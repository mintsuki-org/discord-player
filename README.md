Discord Player
======

discord-player is a "client" (really, it's just a web browser) meant for Discord.

### Why?

Because the official client is proprietary and slow for me, and it does stuff in the
background that hogs my machine :(
I'd use Discord in my browser of choice, but it doesn't run correctly.

### Build Dependencies

#### Debian & Ubuntu

On Debian and Ubuntu, discord-player depends on the following packages:

`build-essential qt5-qmake qtbase5-dev qt5-default qtwebengine5-dev`

#### Arch Linux

On Arch, it depends on qt5, which can be installed with:

`sudo pacman -S qt5`

Then install all selections.

#### Void Linux

Install the following:

`sudo xbps-install -S gcc make qt5-qmake qt5-webengine-devel qt5-webchannel-devel qt5-declarative-devel qt5-location-devel`

#### Fedora

First, install the dependencies:

`qt5-qtbase-devel qt5-qtwebengine qt5-qtwebengine-devel`

On Fedora, the `qmake` binary has a different name than on most distributions (why? no clue), so do the following before building:

`sudo ln -s /usr/bin/qmake-qt5 /usr/bin/qmake`

### Building

To configure the package, use the ./configure script:

    ./configure

Or, if you want to specify a custom prefix:

    ./configure --prefix=/my/custom/path

To build, just run:

    make

To install it run:

    make install

(or `sudo make install` if you need admin privileges)

That is it, have fun! ;)

P.S.: I cannot write C++
