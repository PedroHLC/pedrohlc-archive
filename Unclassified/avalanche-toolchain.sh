#!/usr/bin/sh
# Created by: PedroHLC <pedro.laracampos@gmail.com>
# Downloads and compiles SDL2*, Chipmunk, GLib and libgee for Android (Platform-9 ARM); creates a standalone toolchain; move some useless dinamic librarys
# Compatible with ArchLinux only

# User Configuration
[ "$OUTPATH" == "" ] && export OUTPATH='/tmp/android-toolchain'
[ "$NDK" == "" ] && export NDK='/opt/android-ndk'

# Predefined Info
export ANDROID_PLAT='9'
export ANDROID_ARCH='arm'
export ANDROID_TC="arm-linux-androideabi-4.8"
export CONFLICTING_ITENS='libgthread-*.so* libSDL2.so* libgobject-*.so* libgmodule-*.so* libglib-*.so* libgio-*.so* libgee-*.so*'
export CONFLICTING_ITENSPATH="$OUTPATH/sysroot/usr/lib"
export CONFLICTING_OUTPATH="$CONFLICTING_ITENSPATH/confliting_dynamics"
export ANDROIDPKGS_DEPS='chipmunk ffi iconv gettextlib glib-2.0 gee-0.8 SDL2 SDL2_image SDL2_mixer SDL2_ttf SDL2_gfx'
export ANDROIDPKGS_REPO='https://github.com/PedroHLC/android9arm-archrepo.git'
export ANDROIDPKGS_WORKDIR='/tmp/androidpkgs'
export ANDROIDPKGS_MAKEANDISNTALL='makepkg -i'
export ANDORID_LIBPATH="$NDK/platforms/android-$ANDROID_PLAT/arch-$ANDROID_ARCH/usr/lib"

# Code
if [ ! -f "$NDK/ndk-build" ]; then
	echo "### Please enter a valid NDK path!"
	exit
fi
if [ -d "$ANDROIDPKGS_WORKDIR" ] || [ -d "$OUTPATH" ]; then
	if [ "$FORCE" == "RM" ]; then
		echo 'Removing old files'
		rm -rf "$ANDROIDPKGS_WORKDIR/"
		rm -rf "$OUTPATH/"
	elif [ "$FORCE" != "USE" ]; then
		echo 'You should clean ANDROIDPKGS_WORKDIR and OUTPATH or set FORCE=USE or set FORCE=RM'
		exit
	fi
fi

git clone "$ANDROIDPKGS_REPO" "$ANDROIDPKGS_WORKDIR"
cd "$ANDROIDPKGS_WORKDIR"
for _pkg in ${ANDROIDPKGS_DEPS}; do
	cd "${_pkg}"
	# No need to recompile the already installed ones (:D)
	if [ ! -f "$ANDORID_LIBPATH/lib${_pkg}.so" ]; then
		$ANDROIDPKGS_MAKEANDISNTALL || exit
	fi
	cd ".."
done
cd "$ANDROIDPKGS_WORKDIR"

$NDK/build/tools/make-standalone-toolchain.sh --platform=android-$ANDROID_PLAT --toolchain=$ANDROID_TC --install-dir=$OUTPATH 

mkdir -p $CONFLICTING_OUTPATH
cd "$CONFLICTING_ITENSPATH"
for _item in ${CONFLICTING_ITENS}; do
	mv ${_item} "$CONFLICTING_OUTPATH/"
done

# Fix no 'pthread' founded
cd "$CONFLICTING_ITENSPATH"
ln -sf ./libc.a ./libpthread.a
ln -sf ./libc.so ./libpthread.so