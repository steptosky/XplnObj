#pragma once

/*
**  Copyright(C) 2017, StepToSky
**
**  Redistribution and use in source and binary forms, with or without
**  modification, are permitted provided that the following conditions are met:
**
**  1.Redistributions of source code must retain the above copyright notice, this
**    list of conditions and the following disclaimer.
**  2.Redistributions in binary form must reproduce the above copyright notice,
**    this list of conditions and the following disclaimer in the documentation
**    and / or other materials provided with the distribution.
**  3.Neither the name of StepToSky nor the names of its contributors
**    may be used to endorse or promote products derived from this software
**    without specific prior written permission.
**
**  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**  DISCLAIMED.IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
**  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**
**  Contacts: www.steptosky.com
*/

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
////////////////////////////////////////////////////////////////////////////////////////////////////
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
// TODO tests for transforms without objects.
// Example: Root <- (T)no_obj <- (T)no_obj <- obj3
// Also all this tests need to be rewritten to unit tests, because this module tests is too difficult to understanding.

/*
|* Transform cases.
|* T - anim translate
|* R - anim rotate
|*
|* Keep in mind that the rotate animation can't be without translation animation,
|* so implementation for some test can be skipped. For example R and T|R are identical.
|*
|* The cases 1 and 5 also test algorithm which adds animation
|* translation to the objects which have only rotate animation.
|*
|* The first column is count of implemented tests for the case.
|*
|* =================================================================
|* [02]  Root <-      obj1 <-      obj2 <-      obj3  |  [case 0]  |
|* =================================================================
|* [02]  Root <- (T|R)obj1 <-      obj2 <-      obj3  |  [case 1]  |
|* [02]  Root <-   (R)obj1 <-      obj2 <-      obj3  |  [case 1]  |
|* [01]  Root <-   (T)obj1 <-      obj2 <-      obj3  |  [case 1]  |
|* =================================================================
|* [  ]  Root <-   (T)obj1 <-   (T)obj2 <-      obj3  |  [case 2]  |
|* [  ]  Root <-   (T)obj1 <-   (R)obj2 <-      obj3  |  [case 2]  |
|* [01]  Root <-   (T)obj1 <- (T|R)obj2 <-      obj3  |  [case 2]  |
|* [  ]  Root <-   (R)obj1 <-   (T)obj2 <-      obj3  |  [case 2]  |
|* [01]  Root <-   (R)obj1 <-   (R)obj2 <-      obj3  |  [case 2]  |
|* [  ]  Root <-   (R)obj1 <- (T|R)obj2 <-      obj3  |  [case 2]  |
|* [  ]  Root <- (T|R)obj1 <-   (T)obj2 <-      obj3  |  [case 2]  |
|* [  ]  Root <- (T|R)obj1 <-   (R)obj2 <-      obj3  |  [case 2]  |
|* [  ]  Root <- (T|R)obj1 <- (T|R)obj2 <-      obj3  |  [case 2]  |
|* =================================================================
|* [  ]  Root <- (T|R)obj1 <- (T|R)obj2 <- (T|R)obj3  |  [case 3]  |
|* [  ]  Root <- (T|R)obj1 <- (T|R)obj2 <-   (T)obj3  |  [case 3]  |
|* [  ]  Root <- (T|R)obj1 <- (T|R)obj2 <-   (R)obj3  |  [case 3]  |
|* [  ]  Root <- (T|R)obj1 <-   (R)obj2 <- (T|R)obj3  |  [case 3]  |
|* [  ]  Root <- (T|R)obj1 <-   (R)obj2 <-   (T)obj3  |  [case 3]  |
|* [  ]  Root <- (T|R)obj1 <-   (R)obj2 <-   (R)obj3  |  [case 3]  |
|* [  ]  Root <- (T|R)obj1 <-   (T)obj2 <- (T|R)obj3  |  [case 3]  |
|* [  ]  Root <- (T|R)obj1 <-   (T)obj2 <-   (T)obj3  |  [case 3]  |
|* [  ]  Root <- (T|R)obj1 <-   (T)obj2 <-   (R)obj3  |  [case 3]  |
|*
|* [  ]  Root <-   (R)obj1 <- (T|R)obj2 <- (T|R)obj3  |  [case 3]  |
|* [  ]  Root <-   (R)obj1 <- (T|R)obj2 <-   (T)obj3  |  [case 3]  |
|* [  ]  Root <-   (R)obj1 <- (T|R)obj2 <-   (R)obj3  |  [case 3]  |
|* [  ]  Root <-   (R)obj1 <-   (R)obj2 <- (T|R)obj3  |  [case 3]  |
|* [  ]  Root <-   (R)obj1 <-   (R)obj2 <-   (T)obj3  |  [case 3]  |
|* [02]  Root <-   (R)obj1 <-   (R)obj2 <-   (R)obj3  |  [case 3]  |
|* [  ]  Root <-   (R)obj1 <-   (T)obj2 <- (T|R)obj3  |  [case 3]  |
|* [  ]  Root <-   (R)obj1 <-   (T)obj2 <-   (T)obj3  |  [case 3]  |
|* [  ]  Root <-   (R)obj1 <-   (T)obj2 <-   (R)obj3  |  [case 3]  |
|*	
|* [  ]  Root <-   (T)obj1 <- (T|R)obj2 <- (T|R)obj3  |  [case 3]  |
|* [  ]  Root <-   (T)obj1 <- (T|R)obj2 <-   (T)obj3  |  [case 3]  |
|* [  ]  Root <-   (T)obj1 <- (T|R)obj2 <-   (R)obj3  |  [case 3]  |
|* [  ]  Root <-   (T)obj1 <-   (R)obj2 <- (T|R)obj3  |  [case 3]  |
|* [  ]  Root <-   (T)obj1 <-   (R)obj2 <-   (T)obj3  |  [case 3]  |
|* [  ]  Root <-   (T)obj1 <-   (R)obj2 <-   (R)obj3  |  [case 3]  |
|* [  ]  Root <-   (T)obj1 <-   (T)obj2 <- (T|R)obj3  |  [case 3]  |
|* [02]  Root <-   (T)obj1 <-   (T)obj2 <-   (T)obj3  |  [case 3]  |
|* [  ]  Root <-   (T)obj1 <-   (T)obj2 <-   (R)obj3  |  [case 3]  |
|* =================================================================
|* [  ]  Root <-      obj1 <-   (T)obj2 <-   (T)obj3  |  [case 4]  |
|* [  ]  Root <-      obj1 <-   (T)obj2 <-   (R)obj3  |  [case 4]  |
|* [  ]  Root <-      obj1 <-   (T)obj2 <- (T|R)obj3  |  [case 4]  |
|* [  ]  Root <-      obj1 <-   (R)obj2 <-   (T)obj3  |  [case 4]  |
|* [  ]  Root <-      obj1 <-   (R)obj2 <-   (R)obj3  |  [case 4]  |
|* [  ]  Root <-      obj1 <-   (R)obj2 <- (T|R)obj3  |  [case 4]  |
|* [  ]  Root <-      obj1 <- (T|R)obj2 <-   (T)obj3  |  [case 4]  |
|* [  ]  Root <-      obj1 <- (T|R)obj2 <-   (R)obj3  |  [case 4]  |
|* [  ]  Root <-      obj1 <- (T|R)obj2 <- (T|R)obj3  |  [case 4]  |
|* =================================================================
|* [02]  Root <-       [X] <-      obj2 <- (T|R)obj3  |  [case 5]  |
|* [02]  Root <-       [X] <-      obj2 <-   (R)obj3  |  [case 5]  |
|* [03]  Root <-       [X] <-      obj2 <-   (T)obj3  |  [case 5]  |
|* =================================================================
|*/

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
////////////////////////////////////////////////////////////////////////////////////////////////////
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
