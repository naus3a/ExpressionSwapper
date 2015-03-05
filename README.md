EXPRESSION SWAPPER
==================

A little demo showing how to change people's expression swapping the lower part of their face with an external texture.

It uses Jason Saragih's face tracker and a technique similar to Arturo Castro's and Kyle McDonald's "face cloning" (https://github.com/arturoc/FaceSubstitution): instead of swapping texture between two complete face meshes, it uses a simplified, partial mesh covering only the lower part of the face.

Controls
--------
|- d: toggles a debug view of the original, unedited video feed
|- g: toggles visibility of the lower face mesh
|- space bar: takes a snapshot of your current face expression and uses it

Dependencies
------------
|- OpenFrameworks 8.x
|- ofxCv
|- ofxFaceTracker

License
-------
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.