#!/bin/sh

if [ ! -d "./build" ]
then
	echo "'build' directory does not exist." 

elif [ ! -f "./build/src/rl_server" ] || 
     [ ! -f "./build/src/rocket_league" ]
then
	echo "first run ./build.sh"

elif [ ! -f "./.rl_config.yml" ] ||
     [ ! -d "./src/client/assets" ]
then
		echo "some files are missing, re-clone this repo..."

else
	# install the apps 
	sudo cp ./build/src/rl_server /usr/bin/rl_server
	sudo cp ./build/src/rocket_league /usr/bin/rocket_league

	# create config dir 
	if [ ! -d "/etc/rocket_league" ]
	then
		sudo mkdir /etc/rocket_league
	fi
	
	sudo cp ./.rl_config.yml /etc/rocket_league/.rl_config.yml


	# create data dir 
	if [ ! -d "/var/rocket_league" ]
	then
		sudo mkdir /var/rocket_league
	fi

	sudo cp ./src/client/assets/* /var/rocket_league/

	echo "installation complete"
fi
