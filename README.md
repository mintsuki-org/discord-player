Discord Player
======

Discord Player is a "client" (not really, it's just a web browser, no Discord ToS
violation) for Discord.

### Why?

Because the official client is proprietary and does god-knows-what, no way to know.
Also Discord Player allows for some neat tricks such as being able to copy images
to clipboard and manage multiple profiles.

### Build Dependencies

#### Debian & Ubuntu

On Debian and Ubuntu, discord-player depends on the following packages:

`sudo apt install build-essential cmake qtbase5-dev qt5-default qtwebengine5-dev xdg-utils`

#### Arch Linux

Install the following:

`pacman -S qt5-base qt5-webengine qt5-webchannel qt5-declarative qt5-location xdg-utils cmake`

#### Void Linux

Install the following:

`sudo xbps-install -S gcc make cmake qt5-webengine-devel qt5-webchannel-devel qt5-declarative-devel qt5-location-devel xdg-utils`

#### FreeBSD

Install the following:

`pkg install cmake qt5-buildtools qt5-webengine xdg-utils`

#### Fedora

First, install the dependencies:

`cmake qt5-qtbase-devel qt5-qtwebengine qt5-qtwebengine-devel xdg-utils`

### Building

Just run the "install.sh" script. It will install it in `/usr/local` by default
but this can be overridden with the `PREFIX` variable.
