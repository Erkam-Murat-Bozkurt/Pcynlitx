
FEDORA_RELEASE=~/PCYNLITX.PROJECT.LIBRARY/PCYNLITX_RELEASE_PACKAGES/FEDORA_RELEASE

bash update_fedora_package.sh

cd $FEDORA_RELEASE

sudo chown root:root pcynlitx_fedora

sudo chmod 0777 pcynlitx_fedora

rpmbuild -bb ~/rpmbuild/SPECS/Pcynlitx.spec

sudo chmod 0777 pcynlitx_fedora.rpm
