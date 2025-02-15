#! /bin/bash

if [ -z "$1" ]; then
  exit 1
fi

CODESIGN_ID=$1
VERSION=`cat VERSION`

cd ..

echo "Build CMake Project"

rm -rf build
cmake -B build -DCMAKE_BUILD_TYPE=Release -DCMAKE_OSX_ARCHITECTURES="x86_64;arm64" -DFORMATS="VST3;AU" -DCMAKE_OSX_DEPLOYMENT_TARGET=10.15 && cmake --build build -j11

echo "Package"

mkdir -p dist/macOS/VST3
cp -r build/Plugin_artefacts/Release/VST3/Plugin.vst3 dist/macOS/VST3
cp -r build/Plugin_artefacts/Release/AU/Plugin.component dist/macOS/AU

# NOTE(luca): keep strip disabled while in beta so crash reports will be more informative
llvm-strip $vst3_bin_path && llvm-strip $au_bin_path &&

cd dist/macOS 

codesign -f --deep -o runtime --timestamp --entitlements "entitlements.plist" -s $CODESIGN_ID "VST3/Plugin.vst3"
codesign -f --deep -o runtime --timestamp --entitlements "entitlements.plist" -s $CODESIGN_ID "VST3/Plugin.component"

PKG="Plugin-$VERSION-macOS-setup.pkg"

pkgbuild --root VST3 --install-location "/Library/Audio/Plug-Ins/VST3" --identifier com.company.plugin-vst3 --version $VERSION "Plugin-VST3.pkg"
pkgbuild --root AU --install-location "/Library/Audio/Plug-Ins/Components" --identifier com.chromaaudio.plugin-au --version $VERSION "Plugin-AU.pkg"

productbuild --sign $CODESIGN_ID --distribution distribution.xml $PKG &&

rm -rf VST3 && rm -rf AU && rm Plugin-VST3.pkg && rm Plugin-AU.pkg

xcrun notarytool submit $PKG --keychain-profile "notarytool-password" --wait &&
xcrun stapler staple $PKG &&
xcrun stapler validate $PKG
