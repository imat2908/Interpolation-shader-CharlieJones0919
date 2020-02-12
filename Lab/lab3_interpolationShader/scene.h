/*!
\file scene.h
*/

#ifndef SCENE_H
#define SCENE_H

/*! \class Scene
\brief Contains the variables and functions to instantiate a scene and update it.
*/
class Scene
{
public:
	virtual void initScene(bool isKite, bool &toBeMovedL, bool &toBeMovedR, bool &toBeMovedU, bool &toBeMovedD) = 0; //!< Loads textures, initializes shaders, etc.
	virtual void update(float t) = 0; //!< Currently unused/empty update function. Could be used to animate the scene.
	virtual void render() = 0; //!< Draws the scene.
	virtual void resize(int, int) = 0; //!< Currently unutilized resize function which changes the viewport dimensions.
};

#endif // SCENE_H