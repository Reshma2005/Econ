# Econ

This is practise README


The build environment for which operation has been confirmed is as follows.

Ubuntu 14.04 64 bit, Memory 2 GB or more, available HDD space 30 GB or more.

## Installing the Required Tools

```bash
sudo apt-get install gawk wget git-core diffstat unzip texinfo gcc-multilib build-essential chrpath socat libsdl1.2-dev xterm make \
   xsltproc docbook-utils fop dblatex xmlto autoconf automake libtool libglib2.0-dev libncurses5-dev g++-multilib libssl-dev:i386 \
   libcrypto++-dev:i386 zlib1g-dev:i386 binutils-multiarch-dev
```
## Installing the Go Language

Install the Go language in Linux.

Use the wget command and download the install file to an arbitrary directory.

```bash
wget https://storage.googleapis.com/golang/go1.5.3.linux-amd64.tar.gz
```
Uncompress and expand the downloaded .tar.gz file.
```bash
tar xzvf go1.5.3.linux-amd64.tar.gz
```
Move the expanded "go" directory to below /usr/local.
```bash
sudo mv go /usr/local
```
Add /usr/local/go/bin to the environment variable PATH.

Hint: This procedure must be executed each time the shell that executes build is booted. Command entry can be omitted by describing the command in the login script.
```bash
PATH=$PATH:/usr/local/go/bin
```
## Yocto Environment Setup

Move to inside the SDK directory.

```bash
cd xarina-project/xarina-sdk/
```
Execute the following command to get the build setting file ".config". At this point the settings are the defaults used by e-con.
```bash
make xarina-s-evb-defconfig
```
When the following command is executed, the prebuild files are doownloaded. The build environment is set after the files are downloaded.
```bash
make prebuild
make install
```
## Copying latest bb files

Once the setup is ready, copy the following files into the respective directory and build the SDK.

Go to HyperyonServer directory

```bash
cd ../../
```

Copy all gstreamer1.0* folders and files into gstreamer folder in poky.

```bash
cp -r yocto/gstreamer1.0* xarina-project/poky/meta/recipes-multimedia/gstreamer/
```
Copy libsoup bb file and delete the older one
```bash
cp yocto/libsoup-2.4_2.58.2.bb xarina-project/poky/meta/recipes-support/libsoup/
rm xarina-project/poky/meta/recipes-support/libsoup/libsoup-2.4_2.46.0.bb
```

Copy glib-2.0 bb file and delete the older one
```bash
cp yocto/glib-2.0_2.50.2.bb xarina-project/poky/meta/recipes-core/glib-2.0/
rm xarina-project/poky/meta/recipes-core/glib-2.0/glib-2.0_2.42.1.b
```
Copy libnice bb files and delete the older one
```bash
cp yocto/libnice_0.1.16.bb xarina-project/meta-openembedded/meta-oe/recipes-support/farsight/
rm xarina-project/meta-openembedded/meta-oe/recipes-support/farsight/libnice_0.0.13.bb
```
Copy latest libpcre and delete older one
```bash
cp yocto/libpcre/ xarina-project/poky/meta/recipes-support/
rm xarina-project/poky/meta/recipes-support/libpcre_8.36.bb
```
The files required for building are copied. Now we can build the SDK.


## Yocto Environment Build Execution

The following command is used to build the entire SDK.
```bash
make
```





















