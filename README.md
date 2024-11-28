# Shadow-Casting FOV 3D
A simple 3d shadow-casting fov algorithm

## Algorithm

1. Rectangular view-frustum with 4 diagonal slopes defined starts at center of tileCube
2. Increment one step in the current primary direction/ axis, with corresponding increments in the secondary directions/ axes
3. Set all tileCubes within the incremented view-frustum to seen and record which tileCubes block further vision
4. If necessary, create new rectangular view-frustums and recalculate slopes
5. Repeat steps 2-5 until view-radius reached
6. Repeat for each axis (up, down, north, south, east, west)

## Positives
* No multiplication/ divison

## Negatives
* The tileCubes that lie on the view frustum edges are calculated 3 times, once each for x, y & z
* An int queue is used to record each blocked tileCube
* The rectangular view-frustum merge can be optimized