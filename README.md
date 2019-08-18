Endox-Coin [EDX] integration/staging tree
=====================================

http://endox.chainpages.xyz/

What is the Endox-Coin [EDX] Blockchain?
----------------------------------------
*TODO: Update documentation regarding implemented tech as this section is out of date and much progress and upgrades have been made to mentioned sections...*

### Overview
This blockchain was devised and created through the community for the community (replacing upon community request the old EndoV2 that this is swapping from) 
The goal of this project is to become it's own Operating System for all platforms (As secure and user-friendly as Linux but as beautiful and graceful as Macintosh OS) 

### Blockchain Technology
The Endox [EDX] Blockchain is an experimental smart contract platform protocol that enables 
instant payments to anyone, anywhere in the world in a private, secure manner. 
Endox [EDX] uses peer-to-peer blockchain technology developed by Endox to operate
with no central authority: managing transactions, execution of contracts, and 
issuing money are carried out collectively by the network. Endox [EDX] is the name of 
open source software which enables the use of this protocol.

### Custom Difficulty Retarget Algorithm “VRX”
VRX is designed from the ground up to integrate properly with the Velocity parameter enforcement system to ensure users no longer receive orphan blocks.

### Velocity Block Constraint System
Ensuring Insane stays as secure and robust as possible the CryptoCoderz team have implemented what's known as the Velocity block constraint system. This system acts as third and final check for both mined and peer-accepted blocks ensuring that all parameters are strictly enforced.

### Wish (bmw512) Proof-of-Work Algorithm
Wish or bmw512 hashing algorithm is utilized for the Proof-of-Work function and also replaces much of the underlying codebase hashing functions as well that normally are SHA256. By doing so this codebase is able to be both exponentially lighter and more secure in comparison to reference implementations.

Specifications and General info
------------------
Endox uses 

	libsecp256k1,
	libgmp,
	Boost1.68, OR Boost1.58,  
	Openssl1.02r,
	Berkeley DB 6.2.32,
	QT5.12.1,
	to compile


General Specs

	Block Spacing: 4.5 Minutes
	Stake Minimum Age: 25 Confirmations (PoS-v3) | 30 Minutes (PoS-v2)
	Port: 51441
	RPC Port: 51221


BUILD LINUX
-----------
### Compiling Endox "SatoshiCore" daemon on Ubunutu 18.04 LTS Bionic
### Note: guide should be compatible with other Ubuntu versions from 14.04+

### Become poweruser
```
sudo -i
```
### CREATE SWAP FILE FOR DAEMON BUILD (if system has less than 2GB of RAM)
```
cd ~; sudo fallocate -l 3G /swapfile; ls -lh /swapfile; sudo chmod 600 /swapfile; ls -lh /swapfile; sudo mkswap /swapfile; sudo swapon /swapfile; sudo swapon --show; sudo cp /etc/fstab /etc/fstab.bak; echo '/swapfile none swap sw 0 0' | sudo tee -a /etc/fstab
```

### Dependencies install
```
cd ~; sudo apt-get install -y ntp git build-essential libssl-dev libdb-dev libdb++-dev libboost-all-dev libqrencode-dev libcurl4-openssl-dev curl libzip-dev; apt-get update -y; apt-get install -y git make automake build-essential libboost-all-dev; apt-get install -y yasm binutils libcurl4-openssl-dev openssl libssl-dev; sudo apt-get install -y libgmp-dev; sudo apt-get install -y libtool; cd ~;
```

### Dependencies build and link
```
cd ~; wget http://download.oracle.com/berkeley-db/db-6.2.32.NC.tar.gz; tar zxf db-6.2.32.NC.tar.gz; cd db-6.2.32.NC/build_unix; ../dist/configure --enable-cxx; make; sudo make install; sudo ln -s /usr/local/BerkeleyDB.6.2/lib/libdb-6.2.so /usr/lib/libdb-6.2.so; sudo ln -s /usr/local/BerkeleyDB.6.2/lib/libdb_cxx-6.2.so /usr/lib/libdb_cxx-6.2.so; export BDB_INCLUDE_PATH="/usr/local/BerkeleyDB.6.2/include"; export BDB_LIB_PATH="/usr/local/BerkeleyDB.6.2/lib" cd ~;
```

### GitHub pull (Source Download)
```
cd ~; git clone https://github.com/SaltineChips/Endox
```

### Build Endox daemon
```
cd ~; cd ~/Endox/src; chmod a+x obj; chmod a+x leveldb/build_detect_platform; chmod a+x secp256k1; chmod a+x leveldb; chmod a+x ~/Endox/src; chmod a+x ~/Endox; make -f ~/Endox-Coin/src/makefile/makefile.unix USE_UPNP=-; cd ~; cp -r ~/Endox/src/Endox-Coind /usr/local/bin/Endox-Coind;
```

### Create config file for daemon
```
cd ~; sudo ufw allow 51441/tcp; sudo ufw allow 51221/tcp; sudo ufw allow 22/tcp; sudo mkdir ~/.EDX; cat << "CONFIG" >> ~/.EDX/Endox-Coin.conf
listen=1
server=1
daemon=1
testnet=0
rpcuser=EDXrpcuser
rpcpassword=SomeCrazyVeryVerySecurePasswordHere
rpcport=51221
port=51441
rpcconnect=127.0.0.1
rpcallowip=127.0.0.1
addnode=157.230.107.144
addnode=138.197.161.183
addnode=188.166.109.87
addnode=46.101.73.64
CONFIG
chmod 700 ~/.EDX/Endox-Coin.conf; chmod 700 ~/.EDX; ls -la ~/.EDX
```

### Run Endox daemon
```
cd ~; Endox-Coind; Endox-Coind getinfo
```

### Troubleshooting
### for basic troubleshooting run the following commands when compiling:
### this is for minupnpc errors compiling

```
make clean -f makefile.unix USE_UPNP=-
make -f makefile.unix USE_UPNP=-
```
### Updating daemon in bin directory
```
cd ~; cp -r ~/Endox/src/Endox-Coind /usr/local/bin
```

License
-------

Endox [EDX] is released under the terms of the MIT license. See [COPYING](COPYING) for more
information or see https://opensource.org/licenses/MIT.

Development Process
-------------------

The `master` branch is regularly built and tested, but is not guaranteed to be
completely stable. [Tags](https://github.com/CryptoCoderz/EDX/tags) are created
regularly to indicate new official, stable release versions of Endox [EDX].

The contribution workflow is described in [CONTRIBUTING.md](CONTRIBUTING.md).

The developer [mailing list](https://lists.linuxfoundation.org/mailman/listinfo/bitcoin-dev)
should be used to discuss complicated or controversial changes before working
on a patch set.

Developer Discord can be found at:

Testing
-------

Testing and code review is the bottleneck for development; we get more pull
requests than we can review and test on short notice. Please be patient and help out by testing
other people's pull requests, and remember this is a security-critical project where any mistake might cost people
lots of money.

### Automated Testing

Developers are strongly encouraged to write [unit tests](/doc/unit-tests.md) for new code, and to
submit new unit tests for old code. Unit tests can be compiled and run
(assuming they weren't disabled in configure) with: `make check`

There are also [regression and integration tests](/qa) of the RPC interface, written
in Python, that are run automatically on the build server.

### Manual Quality Assurance (QA) Testing

Changes should be tested by somebody other than the developer who wrote the
code. This is especially important for large or high-risk changes. It is useful
to add a test plan to the pull request description if testing the changes is
not straightforward.
