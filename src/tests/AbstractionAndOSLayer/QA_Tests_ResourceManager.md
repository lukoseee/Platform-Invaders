Notes:
- **These tests are intended for both the Mac and Windows ResourceManagers**
- These tests are highly dependent on the Audio and Image classes

# Making an Image object
-  [ ] Verify making an image : the ResourceManager constructs a suitable image object and returns the reference to such based upon the parameters provided

# Making an Audio object
-  [ ] Verify making an audio object : the ResourceManager constructs a suitable audio object and returns the reference to such based upon the parameters provided

# File Paths
- [ ] Verify suitable filepath construction : the filepaths constructed when creating the image and audio objects, should point to the location on disk where the assets are built (for the executable), e.g. within the .app or Debug folder 
- [ ] Verify the filepaths can be used : ensure other elements of the OS Layer can correctly interact with these filepaths to render images and play audio, i.e. ensure there are no 'file not found errors' 