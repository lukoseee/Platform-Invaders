Notes:
- **These tests are intended for both the Mac and Windows ClockManagers**

# Synchronising the framerate
- [ ] Verify framerate cap implementation : when `synchronizeFrame()` is called, ensure the system 'sleeps' until the target framerate (as defined by `setTargetFramerate()`) is met. Note that: minor deviations in the delay are inevitable due to minor overhead of various operations, so long as the deviations are objectively minimal this is fine.