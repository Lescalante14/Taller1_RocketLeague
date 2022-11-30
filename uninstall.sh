

if [ -f "/usr/bin/rl_server" ] 
then
	echo "removing rl_server..."
	sudo rm /usr/bin/rl_server
fi

if [ -f "/usr/bin/rocket_league" ] 
then
	echo "removing rocket_league..."
	sudo rm /usr/bin/rocket_league
fi

if [ -d "/etc/rocket_league" ] 
then
	echo "removing /etc/rocket_league..."
	sudo rm -rf /etc/rocket_league
fi

if [ -d "/var/rocket_league" ] 
then
	echo "removing /var/rocket_league..."
	sudo rm -rf /var/rocket_league
fi

