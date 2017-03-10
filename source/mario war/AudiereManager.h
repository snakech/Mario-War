#ifndef	AUDIERE_MANAGER_H
#define	AUDIERE_MANAGER_H

#include	<algorithm>
#include	<vector>
#include	<audiere.h>

using	namespace   std;
using	namespace	audiere;

typedef	unsigned long	HSOUND;


class	AudiereManager
{
protected:
	AudiereManager();
	~AudiereManager();

public:
	enum
	{
		LOAD_FAILED = -1
	};
	static	AudiereManager	*GetInstance();
	static	void			Release();

	/*
		interfaces
	*/
	/*
		Name : load
		Desc : load a music or sound ( ogg, it, xm, mod, wav, mp3.etc )
		Param:
			file : the music/sound file
			bStream: if true, the file will be loaded as a stream
					 if you will load a music file, you 'd better set it true
					 load a sound , you can set it false
		Return:the sound/music's id
	*/
	HSOUND	load( const char *file, bool bStream = true );
	
	/*
		Name : play
		Desc : play a sound/music specified by id 
		Param:
			id : the sound/music id, if the id is not valid, then it 
				 will cause a TERMINATE ERROR .
			bLoop: if true, the sound/ music will be loop
		Return:none
	*/
	void	play( HSOUND id, bool bLoop = false );
	void	stop( HSOUND id );
	
	bool	isPlaying( HSOUND id );

	void	reset( HSOUND id );

	void	setVolume( HSOUND id, float volume );
	float	getVolume( HSOUND id );

	void	setPan( HSOUND id, float pan );
	float	getPan( HSOUND id );

	void	setPitchShift( HSOUND id, float shift );
	float	getPitchShift( HSOUND id );

	bool	isSeekable( HSOUND id );

	int		getLength( HSOUND id );

	void	setPosition( HSOUND id, int position );
	int		getPosition( HSOUND id );

private:
	
	AudioDevicePtr				m_device;
	vector<OutputStreamPtr>		m_soundContainer;

private:
	static	AudiereManager		*m_Instance;
	static	int					m_refCount;
};

#endif
