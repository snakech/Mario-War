#include	"AudiereManager.h"

#include	<algorithm>
#include	<vector>


AudiereManager *AudiereManager::m_Instance = NULL;
int				AudiereManager::m_refCount = 0;

AudiereManager::AudiereManager()
{
	m_soundContainer.clear();

	//get device
	m_device	=	OpenDevice();
}

AudiereManager::~AudiereManager()
{
	for( vector<OutputStreamPtr>::iterator i = m_soundContainer.begin(); 
		 i != m_soundContainer.end();
		 ++ i )
	{
		(*i)	=	NULL;
	}
	m_soundContainer.clear();

}

AudiereManager	*AudiereManager::GetInstance()
{
	if( m_Instance == NULL )
	{
		m_Instance	=	new	AudiereManager();
	}

	m_refCount ++;

	return	m_Instance;
}

void	AudiereManager::Release()
{
	m_refCount --;

	if( m_refCount <= 0 )
	{
		delete	m_Instance;
		m_Instance = NULL;
	}
}

HSOUND	AudiereManager::load( const char *file, bool bStream )
{
	OutputStreamPtr	sound = OpenSound( m_device, file, bStream );

	if( sound == NULL )
		return LOAD_FAILED;

	m_soundContainer.push_back( sound );

	return	HSOUND(m_soundContainer.size() - 1);
}

void	AudiereManager::play( HSOUND id, bool bLoop )
{
	m_soundContainer.at( id )->play();

	if( bLoop )
	{
		m_soundContainer.at( id )->setRepeat( true );
	}
}

void	AudiereManager::stop( HSOUND id )
{
	m_soundContainer.at( id )->stop();
}

bool	AudiereManager::isPlaying( HSOUND id )
{
	return m_soundContainer.at( id )->isPlaying();
}

void	AudiereManager::reset( HSOUND id )
{
	m_soundContainer.at( id )->reset();
}

void	AudiereManager::setVolume( HSOUND id, float volume )
{
	m_soundContainer.at( id )->setVolume( volume );
}

float	AudiereManager::getVolume( HSOUND id )
{
	return m_soundContainer.at( id )->getVolume();
}

void	AudiereManager::setPan( HSOUND id, float pan )
{
	m_soundContainer.at( id )->setPan( pan );
}

float	AudiereManager::getPan( HSOUND id )
{
	return	m_soundContainer.at( id )->getPan();
}

void	AudiereManager::setPitchShift( HSOUND id, float shift )
{
	m_soundContainer.at( id )->setPitchShift( shift );
}

float	AudiereManager::getPitchShift( HSOUND id )
{
	return	m_soundContainer.at( id )->getPitchShift();
}

bool	AudiereManager::isSeekable( HSOUND id )
{
	return	m_soundContainer.at( id )->isSeekable();
}

int		AudiereManager::getLength( HSOUND id )
{
	return	m_soundContainer.at( id )->getLength();
}

int		AudiereManager::getPosition( HSOUND id )
{	
	return	m_soundContainer.at( id )->getPosition();
}

void	AudiereManager::setPosition( HSOUND id, int position )
{
	m_soundContainer.at( id )->setPosition( position );
}

