# Builds a .qmod file for loading with QuestPatcher
& $PSScriptRoot/build.ps1

$ArchiveName = "qounters-minus_v1.1.2.qmod"
$TempArchiveName = "qounters-minus_v1.1.2.qmod.zip"

Compress-Archive -Path "./libs/arm64-v8a/libqounters-minus.so", `
    "./libs/arm64-v8a/libbeatsaber-hook_2_3_0.so", `
    "./cover.png", `
    "./mod.json" `
    -DestinationPath $TempArchiveName -Force
Move-Item $TempArchiveName $ArchiveName -Force
