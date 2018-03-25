# Maintainer: pnd4 <kevin[at]pnd4[dot]net>
pkgname=dwm-pnd4
pkgver=6.0
pkgrel=1
pkgdesc="A dynamic window manager for X"
url="http://dwm.suckless.org"
arch=('x86_64')
license=('GPL2')
depends=('libxinerama' 'libxft')
options=(zipman)
provides=('dwm')
conflicts=('dwm-pango')
_source=(http://dl.suckless.org/dwm/dwm-$pkgver.tar.gz
        config.h)
_patches=(00-dwm-6.0-buildflags.diff
          01-dwm-6.0-xft.diff
		  02-dwm-6.0-pertag2.diff
		  03-dwm-6.0-uselessgaps.diff
		  04-dwm-6.0-systray.diff
		  05-dwm-6.0-statuscolors.diff
		  06-dwm-6.0-occupiedcol.diff
		  07-dwm-6.0-monocle_fixes.diff
		  08-dwm-6.0-statusmon.diff
		  09-dwm-6.0-no_title.diff
		  10-dwm-6.0-XKeycodeToKeysym_fix.diff)
source=(${_source[@]} ${_patches[@]})

build() {
    for PATCH in "${_patches[@]}"; do
        msg "${PATCH##*/}" && patch -Np1 -i "${startdir}/${PATCH##*/}"
    done

    cd $srcdir/dwm-$pkgver
    cp $srcdir/config.h config.h

    make X11INC=/usr/include/X11 X11LIB=/usr/lib/X11
}
package() {
    cd $srcdir/dwm-$pkgver
    make PREFIX=/usr DESTDIR=$pkgdir install
    install -m644 -D LICENSE $pkgdir/usr/share/licenses/$pkgname/LICENSE
    install -m644 -D README $pkgdir/usr/share/doc/$pkgname/README
}
md5sums=('8bb00d4142259beb11e13473b81c0857'
<<<<<<< HEAD
         'a12212cf943284bce378c689ac5e5763'
         'b8de5bdd45e3736cf2e6b0277301e196'
=======
         '6d7c73700d10ac93b410385e32e94fe9'
>>>>>>> 15d05ac91be8bcd18eb1fb34835c6d251e1ee9dd
         '10115ccd48a28c7b6bc167257d0c0fb7'
         '0fd771ad51b80c3872c9080bd15f6eea'
         '98d34f02105cf2497d5d1db1b75bd317'
         '6a0f657a18b77764fdd70a819b78412f'
<<<<<<< HEAD
         '80ed7eb56ec61f2c8a261ce7eb944120'
=======
         'e97ce3b7faedb05883a53cc4f970e3c2'
>>>>>>> 15d05ac91be8bcd18eb1fb34835c6d251e1ee9dd
         '5ea175f007b04b82befa36d3c139db04'
         '9a189835b97574a22b21e0249e112ae4'
         '9bdd0c112f1575b69be2967a3c243137'
         'd87223a0c056e59a0dd6a5fba5d0c745'
         'cd20ba50cf16f2cbeea864f99214d485')
