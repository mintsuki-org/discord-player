#!/bin/sh

set -e
set -x

# Defaults
PREFIX="/usr/local"

[ -d generic-webplayer ] || git clone https://github.com/mintsuki/generic-webplayer.git
[ -d generic-webplayer ] && cd generic-webplayer && git pull && cd ..

rm -rf build && mkdir build && cd build
cmake ../generic-webplayer \
    -DCMAKE_INSTALL_PREFIX="$PREFIX" \
    -DPLAYER_NAME="discord-player" \
    -DPLAYER_NICE_NAME="Discord Player" \
    -DPLAYER_WEBAPP_URL="https://discord.com/channels/@me"
make
make install
cd ..

install -d "${PREFIX}/share/applications"
cat <<EOF >"${PREFIX}/share/applications/discord-player.desktop"
[Desktop Entry]
Name=Discord Player
Comment=Qtwebengine wrapper for Discord, because electron sucks.
GenericName=Internet Messenger
Exec=$PREFIX/bin/discord-player
Icon=$PREFIX/share/icons/discord-player.icon
Terminal=false
Type=Application
Categories=Network;InstantMessaging;
EOF
chmod 644 "${PREFIX}/share/applications/discord-player.desktop"

install -d "${PREFIX}/share/icons"
install -m 644 discord-player.icon "${PREFIX}/share/icons/discord-player.icon"
