#include "rendevox.h"

// Entities
entity *entityBuffer;
unsigned int entityBufferSize = 0;

// Projection Matrix
matrix4 projection;

// Camera Position
vector3 camera;

// SDL renderer
SDL_Renderer *sdlRenderer;

int createRender(SDL_Window *sdlWindow) {
	entityBuffer = malloc(0);
	sdlRenderer = SDL_CreateRenderer(sdlWindow, 0, SDL_RENDERER_PRESENTVSYNC);

	if (!sdlRenderer) {
		printf("ERROR: can't craete renderer");
		return 1;
	}

	return 0;
}

void destroyRender() {
	SDL_DestroyRenderer(sdlRenderer);
	free(entityBuffer);
}

void addToEntityBuffer(entity e) {
	entityBufferSize++;
	entityBuffer = realloc(entityBuffer, sizeof(entity) * entityBufferSize);
	entityBuffer[entityBufferSize - 1] = e;
}

void render(int deltaSeconds) {
	// Clear the screen
	SDL_SetRenderDrawColor(sdlRenderer, 0, 0, 0, 0);
	SDL_RenderClear(sdlRenderer);

	for (int e = 0; e < entityBufferSize; e++) {
		// Store the render entity 
		entity renderEntity = entityBuffer[e];

		// Make rotation Z and X
		matrix4 rotZ = { 0 }, rotX = { 0 };

		rotZ = matrixMakeRotationZ((float)deltaSeconds / 1000.0f);
		rotX = matrixMakeRotationX((float)deltaSeconds / 1000.0f);

		// Make translation
		matrix4 trans = { 0 };
		trans = matrixMakeTranslation(0.0f, 0.0f, 0.0f);

		// Create world matrix
		matrix4 world = { 0 };

		world = matrixMakeIdentity();
		world = matrixMultiplyMatrix(&rotZ, &rotX);
		world = matrixMultiplyMatrix(&world, &trans);

		// Create triangles buffer
		triangle *trianglesBuffer = malloc(0);
		unsigned int trianglesBufferSize = 0;

		for (int t = 0; t < renderEntity.mesh.size; t++) {
			triangle projected, transformed;

			// Set transformed triangle
			triangle renderTriangle = renderEntity.mesh.t[t];
			transformed.points[0] = matrixMultiplyVector(&world, &renderTriangle.points[0]);	
			transformed.points[1] = matrixMultiplyVector(&world, &renderTriangle.points[1]);	
			transformed.points[2] = matrixMultiplyVector(&world, &renderTriangle.points[2]);	

			// Use cross product to get surface normal
			vector3 normal, line1, line2;
			
			line1 = vector3Sub(&transformed.points[1], &transformed.points[0]);
			line2 = vector3Sub(&transformed.points[2], &transformed.points[0]);

			normal = vector3CrossProduct(&line1, &line2);
			normal = vector3Normalise(&normal);

			float l = sqrtf(normal.x*normal.x + normal.y*normal.y + normal.z*normal.z);
			normal.x /= l; normal.y /= l; normal.z /= l;

			vector3 cameraRay; 
			cameraRay = vector3Sub(&transformed.points[0], &camera);

			// Add triangle to buffer if we can see it
			if (vector3DotProduct(&normal, &cameraRay) < 0.0f) {
				// Illumination
				vector3 lightDirection = { 0.0f, 1.0f, -1.0f };
				lightDirection = vector3Normalise(&lightDirection);
				
				float dp = max(0.1f, vector3DotProduct(&lightDirection, &normal));
				transformed.color = (color){ round(dp * 255.0f), round(dp * 255.0f), round(dp * 255.0f), 255 };

				// 3D --> 2D
				projected.points[0] = matrixMultiplyVector(&projection, &transformed.points[0]);
				projected.points[1] = matrixMultiplyVector(&projection, &transformed.points[1]);
				projected.points[2] = matrixMultiplyVector(&projection, &transformed.points[0]);
				projected.color = transformed.color;

				projected.points[0] = vector3Div(&projected.points[0], projected.points[0].w);
				projected.points[1] = vector3Div(&projected.points[1], projected.points[1].w);
				projected.points[2] = vector3Div(&projected.points[2], projected.points[2].w);

				// Scale into view
				vector3 offsetView = { 1, 1, 0 };
				projected.points[0] = vector3Add(&projected.points[0], &offsetView); 
				projected.points[1] = vector3Add(&projected.points[1], &offsetView); 
				projected.points[2] = vector3Add(&projected.points[2], &offsetView); 
				projected.points[0].x *= 0.5f * (float)1280;
				projected.points[0].y *= 0.5f * (float)720;
				projected.points[1].x *= 0.5f * (float)1280;
				projected.points[1].y *= 0.5f * (float)720;
				projected.points[2].x *= 0.5f * (float)1280;
				projected.points[2].y *= 0.5f * (float)720;

				trianglesBufferSize++;
				trianglesBuffer = realloc(trianglesBuffer, sizeof(triangle) * trianglesBufferSize);
				trianglesBuffer[trianglesBufferSize - 1] = projected;
			}
		}

		// Sort triangles
		quickSort(trianglesBuffer, 0, trianglesBufferSize - 1);

		// Draw triangle
		for (int i = 0; i < trianglesBufferSize; i++) {
			drawTriangle(sdlRenderer, (vector2){ trianglesBuffer[i].points[0].x, trianglesBuffer[i].points[0].y },
				(vector2){ trianglesBuffer[i].points[1].x, trianglesBuffer[i].points[1].y },
				(vector2){ trianglesBuffer[i].points[2].x, trianglesBuffer[i].points[2].y }, trianglesBuffer[i].color);
		}
	}

	// Render buffer
	SDL_RenderPresent(sdlRenderer);
}
