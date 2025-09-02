Notes:
- **These tests are intended for both the Mac and Windows UserInputManagers**

# Getting User Input
- [ ] Verify User Input can be fetched : once a key is pressed, a call to getNextInput() should return a string of the key pressed
- [ ] Verify multiple inputs are handled : if various keys are pressed, ensure all keys are returned by various calls to getNextInput()
- [ ] Verify safety of getNextInput : is no key is pressed and getNextInput() is called, the program should not crash. Note: the importance of this test is for system robustness
- [ ] Verify consistency across OSs : the key value strings returned by getNextInput() should be the same across OSs for a given key