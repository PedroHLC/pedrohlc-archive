#======================================================================
# module RMXOS
#======================================================================

module RMXOS
	
	# these values MUST correspond with the values specified in the RMXP client
	RESULT_SUCCESS = 0
	RESULT_DENIED = 1
	RESULT_FAIL = 2
	RESULT_ALTFAIL = 3
	
	GROUP_ADMIN = 10
	GROUP_2NDADMIN = 9
	GROUP_MOD = 8
	GROUP_PLAYER = 0
	
	#==================================================================
	# module RMXOS::Data
	#------------------------------------------------------------------
	# Contains constants.
	#==================================================================
	
	module Data
		
		Delimiter	= '--------------------------------------------------------------------------'
		Header		= '=========================================================================='
		PressEnter	= 'Press ENTER to continue.'
		Version		= 'RMX-OS Server vVERSION'
		# Basic constants
		AreYouSure			= 'Are you sure?'
		BuddyNoAdd			= 'You have not accepted the buddy list invitation.'
		CommandPrompt		= 'Ruby Prompt active.'
		CommandPromptSign	= '>> '
		CTRLC				= 'Press CTRL+C to shut down RMX-OS.'
		ConfigurationError	= 'Error: The configuration file was not set up properly!'
		DoYouAccept			= 'Do you accept?'
		ExtensionsLoading	= 'Loading extensions...'
		GuildNoJoin			= 'You have not accepted the guild invitation.'
		GuildNoTransfer		= 'You have not accepted the guild leadership transfer request.'
		Host				= 'Host'
		InboxFull			= 'Your PM inbox is full.'
		InvalidSyntax		= 'Invalid Syntax!'
		Kickall				= 'All players have been kicked.'
		MySQLOptimizing		= '> Optimizing database tables...'
		NewPMs				= 'You have new PMs.'
		NoExtensions		= 'No extensions found.'
		NoRequest			= 'There is currently no action that requires an answer from you.'
		PasswordChanged		= 'The password has been changed.'
		PasswordChanging	= 'You are about to change your password.'
		PasswordIncorrect	= 'The password is incorrect.'
		PasswordNoChange	= 'The password has not been changed.'
		PMDeletedAll		= 'You have deleted all PMs in your inbox.'
		PMDeletingAll		= 'You are about to delete all PMs in your inbox.'
		PMDeletingUnreadAll	= 'You are about to delete all PMs in your inbox. Some of them are marked as unread.'
		PMNoDeletion		= 'No PMs have been deleted.'
		Restart				= 'Restart in:'
		ScriptExecuted		= 'Script successfully executed.'
		Server				= 'Server'
		ShuttingDown		= 'RMX-OS Server is shutting down...'
		ShuttingDownForced	= 'RMX-OS Server is being terminated...'
		Shutdown			= 'RMX-OS Server has shut down.'
		ShutdownForced		= 'RMX-OS Server has been terminated.'
		StartingServer		= 'RMX-OS Server is starting up...'
		TradeNoRequest		= 'You have not accepted the trade request.'
		UnexpectedError		= 'Unexpected error occured!'
		
		# Special constants
		ActionDenied			= 'You do not have permission to ACTION \'PLAYER\'.'
		ActionDenied2			= 'You do not have permission to use ACTION.'
		ActionSuccess			= 'Player \'PLAYER\' has been ACTION.'
		BuddyAdd				= '\'PLAYER\' wants to be buddies with you.'
		BuddyAddedPlayer		= 'You and \'PLAYER\' are now buddies.'
		BuddyAddingPlayer		= 'You requested to add \'PLAYER\' to your buddy list.'
		BuddyRemovingPlayer		= 'You are about to remove \'PLAYER\' from your buddy list.'
		BuddyNoAddPlayer		= '\'PLAYER\' has not accepted the buddy list invitation.'
		BuddyNoRemovePlayer		= '\'PLAYER\' was not removed from your buddy list.'
		BuddyRemovePlayer		= 'You and \'PLAYER\' are not buddies anymore.'
		ClientError				= 'Client ID (NAME) at TIME has caused an error:'
		ExtensionFileError		= 'Error: \'FILE\' does not exist.'
		ExtensionInitError		= 'Error: \'FILE\' could not be initialized.'
		ExtensionLoadError		= 'Error: \'FILE\' could not be loaded.'
		ExtensionRunError		= 'Error: \'FILE\' caused an error.'
		ExtensionVersionError	= 'Error: \'FILE\' requires at least RMX-OS Version VERSION.'
		ExtensionLoaded			= '\'FILE\' vVERSION loaded and initialized.'
		GroupChangeSuccess		= 'The usergroup of player \'PLAYER\' has been changed.'
		GuildCreateFail			= 'Guild \'GUILD\' already exists.'
		GuildCreateSuccess		= 'Guild \'GUILD\' has been created.'
		GuildDisbanded			= 'The guild \'GUILD\' has been disbanded.'
		GuildDisbanding			= 'You are about to disband your guild \'GUILD\'.'
		GuildInvitation			= 'You have been invited to join the guild \'GUILD\'.'
		GuildInvited			= 'You have invited \'PLAYER\' to join your guild.'
		GuildJoined				= 'You have joined the guild \'GUILD\'.'
		GuildJoinedPlayer		= '\'PLAYER\' has joined the guild.'
		GuildLeader				= 'You are the new guild leader of \'GUILD\'.'
		GuildLeaderPlayer		= '\'PLAYER\' is the new guild leader of \'GUILD\'.'
		GuildLeaving			= 'You are about to leave the guild \'GUILD\'.'
		GuildNoDisband			= 'The guild \'GUILD\' has not been disbanded.'
		GuildNoJoinPlayer		= '\'PLAYER\' has not accepted the guild invitation.'
		GuildNoLeave			= 'You have not left the guild \'GUILD\'.'
		GuildNoRemove			= '\'PLAYER\' has not been removed from your guild.'
		GuildNotExist			= 'Guild \'GUILD\' does not exist.'
		GuildNoTransferPlayer	= '\'PLAYER\' has not accepted the guild leadership transfer request.'
		GuildRemoving			= 'You are about to remove \'PLAYER\' from your guild.'
		GuildRemoved			= 'You are not a member of guild \'GUILD\' anymore.'
		GuildRemovedPlayer		= 'Player \'PLAYER\' is not a member of guild \'GUILD\' anymore.'
		GuildTransferring		= 'You are about to pass your guild leadership of \'GUILD\' to \'PLAYER\'.'
		GuildTransfer			= 'Your guild leader \'PLAYER\' wants to transfer the leadership to you.'
		InboxStatus				= 'Your inbox status is STATUS.'
		InboxEmpty				= 'Your inbox is already empty.'
		InboxFullPlayer			= 'The inbox of player \'PLAYER\' is full.'
		MySQLConnecting			= '> Connecting to MySQL database \'DATABASE\'...'
		PasswordForcing			= 'You are about to change the password of \'ENTITY\'.'
		PlayerAlreadyGuild		= 'Player \'PLAYER\' is already member of another guild.'
		PlayerNotExist			= 'Player \'PLAYER\' does not exist.'
		PlayerNotOnline			= 'Player \'PLAYER\' does not exist or is not online.'
		PlayerNotOnlineMap		= 'Player \'PLAYER\' does not exist, is not online or is not on the same map.'
		PlayerNotOnMap			= 'Player \'PLAYER\' is not online or is not on the same map.'
		PMDeleted				= 'You have deleted PM MESSAGEID.'
		PMDeleting				= 'You are about to delete PM MESSAGEID.'
		PMDeletingUnread		= 'You are about to delete the unread PM MESSAGEID.'
		PMNotExist				= 'PM \'MESSAGEID\' does not exist.'
		PMSent					= 'PM has been sent to player \'PLAYER\'.'
		StartSuccess			= 'RMX-OS Server has started successfully at TIME.'
		SocketStarting			= '> Starting TCP Server at \'IP:PORT\'...'
		TableOptimizing			= '    > Optimizing table \'TABLE\'...'
		TradeNoRequestPlayer	= '\'PLAYER\' has not accepted the trade request.'
		TradeRequestedPlayer	= 'You requested to trade with \'PLAYER\'.'
		TradeRequestPlayer		= '\'PLAYER\' has requested to trade with you.'
		UnknownClientError		= 'A client at TIME has caused an error:'
		
		# Other data constants
		ColorError	= "\xFF\xBF\x3F"
		ColorInfo	= "\xBF\xBF\xFF"
		ColorOK		= "\x1F\xFF\x1F"
		ColorNormal	= "\xFF\xFF\xFF"
		
	end
		
	#==================================================================
	# module RMXOS::Debug
	#------------------------------------------------------------------
	# Contains debug constants.
	#==================================================================
	
	module Debug
		
		# Debug constants
		ClientConnect		= 'Client connected.'
		ClientDisconnect	= 'Client disconnected.'
		ClientError			= 'Client disconnection caused problems.'
		ClientFailed		= 'Client problem detected.'
		ConnectionReceived	= 'New connection received.'
		DbConnectionBusy	= 'Reconnecting to database...'
		DbConnectionOk		= 'Database reconnection successful.'
		ExtensionFail		= 'Extension crash detected.'
		MaintenanceThread	= 'Maintenance Thread'
		MainThread			= 'Main Thread'
		PingFailed			= 'Ping on client failed.'
		ServerForceStopped	= 'Server forcibly stopped.'
		ServerForceStopping	= 'Server forcibly stopping...'
		ServerStarted		= 'Server started.'
		ServerStarting		= 'Server starting...'
		ServerStopped		= 'Server stopped.'
		ServerStopping		= 'Server stopping...'
		ThreadStart			= 'Thread started.'
		ThreadStop			= 'Thread stopped.'
		
	end

end
