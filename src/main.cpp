//main.cpp
//
// Copyright Enrico <naus3a> Viola 2015
// This file is part of ExpressionSwapper.
//
//ExpressionSwapper is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.
//
//ExpressionSwapper is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with ExpressionSwapper.  If not, see <http://www.gnu.org/licenses/>.

#include "testApp.h"
#include "ofAppGlutWindow.h"

int main() {
	ofAppGlutWindow window;
	ofSetupOpenGL(&window, 1280, 720, OF_WINDOW);
	ofRunApp(new testApp());
}
