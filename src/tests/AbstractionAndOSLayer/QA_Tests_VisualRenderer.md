Notes:
- **These tests are intended for both the Mac and Windows VisualRenderer**
- These tests are highly dependent on the Image class
- These tests often require interacting elements between the different functions they are testing

# Window Creation
- [ ] Verify window creation : when createWindow() is called a window should be displayed.
- [ ] Verify window is created of specified size : when createWindow() is called with width, height dimension parameters, a window should be created of the specified size.
- [ ] Verify no more than one window can be made : any subsequent calls to createWindow() following the initial one, should do nothing.

# Rendering an Image
- [ ] Verify an image can be rendered : given a valid filepath, the visual renderer should display an image on the screen once renderImage() is called with a properly initalised Image* parameter.
- [ ] Verify the image is rendered at the right location : as above, the image should be rendered at the specified x, y pixel coordinate location
- [ ] Verify multiple renderings of the same Image* does nothing : subsequent calls to renderImage() on the same Image* object should do nothing
- [ ] Verify multiple images of the same filepath can be rendered : ensure multiple calls to renderImage() on different Image* objects with the same filepath, renders multiple of the same image/sprite.

# Moving a rendered Image
- [ ] Verify an image can be moved to a new location : once an image has been rendered, ensure the image can be moved via a call to moveRenderedImage(). Note: this does *not* mean rendering a 2nd copy of the image at this new location.
- [ ] Verify an image cannot be moved, if it is not already rendered : if an image has not yet been rendered, any calls to move this rendered image should fail (i.e. do nothing)

# Removing an Image
- [ ] Verify an image can be removed : once an image is rendered, a call to removeImage() on the given image should remove the image from the display
- [ ] Verify a removed image can be re-rendered : once an image is rendered, removed and then re-rendered, ensure it reappears as expected.
- [ ] Verify an image cannot be removed if it is not rendered : calls to removeImage() on a non-rendered Image* should do nothing.  

