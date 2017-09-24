# Art-Net console

This is a really minimalist Art-Net console, built on the top of Qt and libartnet

## Installing lib ArtNet (Linux)

You can do the following:

    git clone https://github.com/OpenLightingProject/libartnet.git
    cd libartnet
    autoreconf --install
    ./configure --prefix=/usr/
    make
    sudo make install

## Building Art-Net console

    git clone https://github.com/Gregwar/ArtNet-Console.git
    cd ArtNet-Console
    qmake-qt4
    make
