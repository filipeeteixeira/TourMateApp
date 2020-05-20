//
// Created by breno on 5/12/2020.
//

#ifndef TOURMATEAPP_MENU_H
#define TOURMATEAPP_MENU_H

#include <string>
#include <iostream>
#include "Utils.h"
#include "DataReader.h"
#include "GraphBuilder/Vertex.h"
#include "GraphBuilder/Edge.h"
#include "User.h"

void menu();
void showMainMenu();

void showUserOptions();
void userOptions();

void showTourOptions();
void tourOptions();

void showGraphOptions();
void graphOptions();

void showGraphSelectionOptions();
void chooseGraphOptions();
#endif //TOURMATEAPP_MENU_H
