$timestamp = Get-Date -Format "MM-dd HH:mm:ss.fff"
adb logcat -T "$timestamp" main-modloader:W QuestHook[qounters-minus`|v1.0.0]:* AndroidRuntime:E *:S
