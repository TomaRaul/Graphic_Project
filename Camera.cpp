#include "Camera.hpp"

namespace gps {

    //Camera constructor
    Camera::Camera(glm::vec3 cameraPosition, glm::vec3 cameraTarget, glm::vec3 cameraUp) {
        //TODO
        this->cameraPosition = cameraPosition;
        this->cameraTarget = cameraTarget;
        this->cameraUpDirection = cameraUp;

        //XXX
       // Calculam initial directia front (in functie de pozitie si target)
        this->cameraFrontDirection = glm::normalize(cameraTarget - cameraPosition);

        // Setam yaw si pitch la valori implicite
        this->yaw = -90.0f;  // Privim spre -Z
        this->pitch = 0.0f;

        // Actualizam axele camerei
        updateCameraVectors();
        
    }

    //return the view matrix, using the glm::lookAt() function
    glm::mat4 Camera::getViewMatrix() {
        //TODO

        //return glm::lookAt(cameraPosition, cameraTarget, this->cameraUpDirection);
        return glm::lookAt(cameraPosition, cameraPosition + cameraFrontDirection, this->cameraUpDirection);
    }

    //update the camera internal parameters following a camera move event
    void Camera::move(MOVE_DIRECTION direction, float speed) {
        //TODO
        //XXXX
        if (direction == MOVE_FORWARD) {
            cameraPosition += speed * cameraFrontDirection;
        }
        if (direction == MOVE_BACKWARD) {
            cameraPosition -= speed * cameraFrontDirection;
        }
        if (direction == MOVE_LEFT) {
            cameraPosition -= cameraRightDirection * speed;
        }
        if (direction == MOVE_RIGHT) {
            cameraPosition += cameraRightDirection * speed;
        }
    }

    //update the camera internal parameters following a camera rotate event
    //yaw - camera rotation around the y axis
    //pitch - camera rotation around the x axis
    void Camera::rotate(float pitchOffset, float yawOffset) {
        //TODO
        //XXXX
        yaw += yawOffset;
        pitch += pitchOffset;

        // Limitam pitch-ul între -89 si 89 grade pentru a evita inversarea camerei
        if (pitch > 89.0f) pitch = 89.0f;
        if (pitch < -89.0f) pitch = -89.0f;

        // Recalculam directiile camerei
        updateCameraVectors();
    }

    // Actualizeaza directiile camerei dupa o rotatie
    void Camera::updateCameraVectors() {
        glm::vec3 front;
        front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        front.y = sin(glm::radians(pitch));
        front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        cameraFrontDirection = glm::normalize(front);

        // Recalculam axa dreapta si sus
        cameraRightDirection = glm::normalize(glm::cross(cameraFrontDirection, cameraUpDirection));
    }
}
