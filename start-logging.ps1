$timestamp = Get-Date -Format "MM-dd HH:mm:ss.fff"
adb logcat -T "$timestamp" main-modloader:W QuestHook[qounters-minus`|v0.1.4]:* AndroidRuntime:E *:S
