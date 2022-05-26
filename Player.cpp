//
// Created by Admin on 2022-05-25.
//

#include "Player.h"
#include "Converter.h"
#include "Mine.h"

Player::Player(int playerPosX, int playerPosZ) {
    relativePosX = playerPosX;
    relativePosZ = playerPosZ;
    relativeFocusX = 0;
    relativeFocusZ = 0;
    playerSize = 0.7f;
}

void Player::movePlayer() {
    if (IsKeyPressed(KEY_D)) {
        relativePosX += 1;
    } else if (IsKeyPressed(KEY_A)) {
        relativePosX -= 1;
    } else if (IsKeyPressed(KEY_S)) {
        relativePosZ += 1;
    } else if (IsKeyPressed(KEY_W)) {
        relativePosZ -= 1;
    }
    Player::limitMove();
}

void Player::limitMove() {
    int *mapLengthArr = Converter::getMapLength();
    int maxPosX = mapLengthArr[0] - 1;
    int maxPosZ = mapLengthArr[1] - 1;

    if (relativePosX < 0)
        relativePosX = 0;
    if (relativePosX > maxPosX)
        relativePosX = maxPosX;
    if (relativePosZ < 0)
        relativePosZ = 0;
    if (relativePosZ > maxPosZ)
        relativePosZ = maxPosZ;
}

void Player::drawPlayer() {
    const Vector3 &playerPos = Converter::translateToAbsolute(relativePosX, relativePosZ);
    DrawCube(playerPos, playerSize, playerSize, playerSize, RED);
    DrawCubeWires(playerPos, playerSize, playerSize, playerSize, MAROON);
}

void Player::drawFocus() {
    if(relativeFocusX >= 0 && relativeFocusZ >= 0) {
        const Vector3 &focusPos = Converter::translateToAbsolute(relativeFocusX, relativeFocusZ);
        DrawCubeWires(focusPos, playerSize, playerSize, playerSize, GREEN);
    }
}

void Player::choiceFocus() {
    if (IsKeyPressed(KEY_RIGHT)) {
        relativeFocusX += 1;
    } else if (IsKeyPressed(KEY_LEFT)) {
        relativeFocusX -= 1;
    } else if (IsKeyPressed(KEY_DOWN)) {
        relativeFocusZ += 1;
    } else if (IsKeyPressed(KEY_UP)) {
        relativeFocusZ -= 1;
    }
    Player::limitFocus();
}

void Player::limitFocus() {
    if(relativeFocusX - relativePosX > 1)
        relativeFocusX -= 1;
    if(relativeFocusX - relativePosX < -1)
        relativeFocusX += 1;
    if(relativeFocusZ - relativePosZ > 1)
        relativeFocusZ -= 1;
    if(relativeFocusZ - relativePosZ < -1)
        relativeFocusZ += 1;
}

bool Player::isStepOnMine(Mine *mine) {
    return !(mine->checkMinePos(relativePosX, relativePosZ));
}

int *Player::getRelativePlayerPos() {
    int *playerPosArr = new int[2];
    playerPosArr[0] = relativePosX;
    playerPosArr[1] = relativePosZ;
    return playerPosArr;
}

