set -e

sudo apt-key adv --fetch-keys http://repos.codelite.org/CodeLite.asc

sudo apt-add-repository 'deb http://repos.codelite.org/wx3.1.2/debian/ buster libs'

sudo apt-get update -y

sudo apt-get install libwxbase3.0-0v5

sudo apt-get install libwxbase3.0-dev

sudo apt-get install libwxgtk3.0-0v5

sudo apt-get install libwxgtk3.0-dev

sudo apt-get install libwxgtk3.0-gtk3-0v5

sudo apt-get install libwxgtk3.0-gtk3-dev

sudo apt-get install wx3.0-headers

sudo apt-get install wx3.0-i18n

sudo apt-get install wx-common

sudo apt-get install fonts-liberation

sudo apt-get install fonts-linuxlibertine
