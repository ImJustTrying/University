/*
 * Kevin Vicente
 * January 2020
 *
 * This is the program for the first problem set. Helper functions are defined first,
 * then the specified functions from the document, the tests, and finally the main
 * program at the bottom of the script. All code is written solely by myself.
 */

// These are helper functions 
function pixelAvg(p) {
  if (p.length !== 3) { return null; }
  else { return (p[0] + p[1] + p[2]) / 3; }
}

function pixelAdd(a, b) {
  if (a.length !==3 || b.length !== 3) { return null; }
  else { a[0] += b[0]; a[1] += b[1]; a[2] += b[2]; return a; }
}

function pixelMult(p, s) {
  if (p.length !== 3) { return null; }
  else { p[0] *= s; p[1] *= s; p[2] *= s; return p; }
}

function red(p) { return [p[0], 0, 0]; }
function gray(p) { const avg = pixelAvg(p); return [avg, avg, avg]; }

// This will take a pixels index in an image and return an array with the
// adjacent neighboring pixels 
function getPixelNeighbors(img, i, j) {
  if (i < 0 || j < 0 || i >= img.width || j >= img.height) { return []; }
  let pixels = [img.getPixel(i,j)];
  if (i !== 0) { pixels.push(img.getPixel(i - 1, j)); }
  if (j !== 0) { pixels.push(img.getPixel(i, j - 1)); }
  if (i !== img.width - 1) { pixels.push(img.getPixel(i + 1, j)); }
  if (j !== img.height - 1) { pixels.push(img.getPixel(i, j + 1)); }

  if (i !== 0 && j !== 0) { pixels.push(img.getPixel(i - 1, j - 1)); }
  if (i !== 0 && j !== img.height - 1) { pixels.push(img.getPixel(i - 1, j + 1)); }
  if (i !== img.width - 1 && j !== 0) { pixels.push(img.getPixel(i + 1, j - 1)); }
  if (i !== img.width - 1 && j !== img.height - 1) { pixels.push(img.getPixel(i + 1, j + 1)); }
  return pixels;
}



// The following are the functions specified in the hw document
function removeBlueAndGreen(img) {
  let newImg = img.copy();
  for (let i = 0; i < newImg.width; i += 1) {
    for (let j = 0; j < newImg.height; j += 1) {
      const pixel = newImg.getPixel(i,j);
      newImg.setPixel(i,j, [pixel[0], 0, 0]);
    }
  }
  return newImg;
}

function makeGrayscale(img) {
  let newImg = img.copy();
  for (let i = 0; i < newImg.width; i += 1) {
    for (let j = 0; j < newImg.height; j += 1) {
      const avg = pixelAvg(img.getPixel(i,j));
      newImg.setPixel(i,j,[avg,avg,avg]);
    }
  }
  return newImg;
}

// imageMap(img: Image, f: (p: Pixel) => Pixel): Image
function imageMap(img, f) {
  let newImg = img.copy();
  for (let i = 0; i < newImg.width; i += 1) {
    for (let j = 0; j < newImg.height; j += 1) {
      const pixel = newImg.getPixel(i,j);
      newImg.setPixel(i,j, f(pixel));
    }
  }
  return newImg;
}

function mapToGrayscale(img) {
  return imageMap(img, gray);
}

function mapToRed(img) {
  return imageMap(img, red);
}

function highlightEdges(img) {
  let newImg = img.copy();
  if (newImg.width <= 1) { return newImg; }
  for (let i = 0; i < newImg.width; i += 1) {
    for (let j = 0; j < newImg.height; j += 1) {
      // Get the pixel values from the original image since getting them from
      // the new image results in incorrect values
      const current_pixel = img.getPixel(i, j);
      const neighbor_pixel = img.getPixel((i === newImg.width - 1) ? i - 1 : i + 1, j);
      const highlight = Math.abs(pixelAvg(current_pixel) - pixelAvg(neighbor_pixel));
      newImg.setPixel(i,j, [highlight, highlight, highlight]);
    }
  }
  return newImg;
}

function blur(img) {
  let newImg = img.copy();
  for (let i = 0; i < img.width; i += 1) {
    for (let j = 0; j < img.height; j += 1) {
      const neighbors = getPixelNeighbors(img, i, j);
      let average = [0,0,0];
      // Average the neighboring pixels into one and set the pixel at that index to the average
      for (let k = 0; k < neighbors.length; k += 1) {
        average = pixelAdd(average, neighbors[k]);
      }
      average = pixelMult(average, 1 / neighbors.length);
      newImg.setPixel(i, j, average);
    }
  }
  return newImg;
}

// Tests below
/*
// These functions are for testing
function pixelEq (p1, p2) {
  const epsilon = 0.002;
  for (let i = 0; i < 3; ++i) {
    if (Math.abs(p1[i] - p2[i]) > epsilon) {
      return false;
    }
  }
  return true;
};

// Since javascript arrays are judged equivalent by reference value (i.e. arrays are equal if they
// point to the same array), we need to write our own pixelArrayEq that checks equivalence for each value
function pixelArrayEq(a1, a2) {
  if (a1.length !== a2.length) { return false; }
  for (let i = 0; i < a1.length; i += 1) {
    if (!pixelEq(a1[i], a2[i])) { return false; }
  }
  return true;
}


test("removeBlueAndGreen correctness", function() {
  const testImg = lib220.createImage(10, 10, [1,1,1]);
  const redImg = removeBlueAndGreen(testImg);
  for (let i = 0; i < 10; i += 1) {
    for (let j = 0; j < 10; j += 1) {
      assert(pixelEq(redImg.getPixel(i,j), [1,0,0]));
    }
  }
});

test("makeGrayscale correctness", function () {
  const grayImg = makeGrayscale(lib220.createImage(10, 10, [0.2,0.5,0.8]));
  const expectedAvg = pixelAvg([0.2,0.5,0.8]);
  const expectedPixel = [expectedAvg, expectedAvg, expectedAvg];
  for (let i = 0; i < 10; i += 1) {
    for (let j = 0; j < 10; j += 1) {
      assert(pixelEq(grayImg.getPixel(i,j), expectedPixel));
    }
  }
});

test("imageMap make image black", function () {
  const testImg = lib220.createImage(10, 10, [0.2, 0.5, 0.8]);
  // Make the entire image black
  const blackImg = imageMap(testImg, function(p) { p[0] = 0; p[1] = 0; p[2] = 0; return p; });
  for (let i = 0; i < 10; i += 1) {
    for (let j = 0; j < 10; j += 1) {
      assert(pixelEq(blackImg.getPixel(i,j), [0,0,0]));
    }
  }
});

test("highlightEdges on solid image", function () {
  const testImg = lib220.createImage(10, 10, [0,0,0]);
  const sameImg = highlightEdges(testImg);
  // Check that the image is exactly the same
  for (let i = 0; i < 10; i += 1) {
    for (let j = 0; j < 10; j += 1) {
      assert(pixelEq(sameImg.getPixel(i,j), [0,0,0]));
    }
  }
});

test("highlightEdges on single edge", function() {
  // This is an image with a single vertical white stripe one pixel wide
  let edgeImg = lib220.createImage(2, 10, [0,0,0]);
  for (let i = 0; i < 10; i += 1) { edgeImg.setPixel(0,i, [1,1,1]); }
  // The output of highlightEdges should be a fully white image
  const whiteImg = highlightEdges(edgeImg);
  for (let i = 0; i < 10; i += 1) {
    assert(pixelEq(whiteImg.getPixel(0,i), [1,1,1]));
    assert(pixelEq(whiteImg.getPixel(1,i), [1,1,1]));
  }
});

test("pixel (vector) operations", function() {
  let pixel = [1,2,3];
  pixel = pixelAdd(pixel, [1,2,3]);
  assert(pixelEq(pixel, [2,4,6]));
  pixel = pixelMult(pixel, 2);
  assert(pixelEq(pixel, [4,8,12]));
  const expectedAvg = (4 + 8 + 12) / 3;
  assert(pixelAvg(pixel) === expectedAvg);
});

test("getPixelNeighbors middle pixel", function() {
  const pixel = [0.2, 0.5, 0.8];
  const img = lib220.createImage(3, 3, pixel);
  // getPixelNeighbor should return an array with 9 copies of pixel 
  assert(pixelArrayEq(getPixelNeighbors(img, 1, 1), [pixel,pixel,pixel,pixel,pixel,pixel,pixel,pixel,pixel]));
});

// Here we test all the cases where getPixelNeighbors should return an array with less than
// 9 adjacent pixels
test("getPixelNeighbors edge cases", function() {
  const pixel = [0.2, 0.5, 0.8];
  const thinImg = lib220.createImage(1, 3, pixel);
  const wideImg = lib220.createImage(3, 1, pixel);
  const pixelImg = lib220.createImage(1, 1, pixel);
  const normalImg = lib220.createImage(3, 3, pixel);

  // Out of bound indices
  assert(pixelArrayEq(getPixelNeighbors(normalImg, -1, -1), []));
  assert(pixelArrayEq(getPixelNeighbors(normalImg, 3, 3), []));

  assert(pixelArrayEq(getPixelNeighbors(thinImg, 0, 1), [pixel, pixel, pixel]));
  assert(pixelArrayEq(getPixelNeighbors(wideImg, 1, 0), [pixel, pixel, pixel]));
  assert(pixelArrayEq(getPixelNeighbors(pixelImg, 0, 0), [pixel]));

  // Now we check for edge cases with a full (width and height greater than one) image
  assert(pixelArrayEq(getPixelNeighbors(normalImg, 0, 0), [pixel,pixel,pixel,pixel]));
  assert(pixelArrayEq(getPixelNeighbors(normalImg, 1, 0), [pixel,pixel,pixel,pixel,pixel,pixel]));
});

test("blur on solid image", function () {
  const pixel = [0.2, 0.5, 0.8];
  const img = lib220.createImage(3, 3, pixel);
  const blurredImg = blur(img);
  for (let i = 0; i < blurredImg.width; i += 1) {
    for (let j = 0; j < blurredImg.height; j += 1) {
      assert(pixelEq(blurredImg.getPixel(i,j), pixel));
    }
  }
});

test("blur on outlined image", function () {
  const pixel = [1, 1, 1];
  let img = lib220.createImage(3, 3, pixel);
  // This makes the image have a colored outline with a black pixel in the middle
  img.setPixel(1,1, [0,0,0]);
  const blurredImg = blur(img);

  // This is the expected average value for the middle pixel, the pixels adjacent to
  // the middle, and the pixels diagonally adjacent to the middle in that order
  const expectedAvgMiddle = [8/9, 8/9, 8/9];
  const expectedAvgEdge = [5/6, 5/6, 5/6];
  const expectedAvgCorner = [3/4, 3/4, 3/4];

  for (let i = 0; i < blurredImg.width; i += 1) {
    for (let j = 0; j < blurredImg.height; j += 1) {
      if (i === 1 && j === 1) { assert(pixelEq(blurredImg.getPixel(i,j), expectedAvgMiddle)); }
      else if ((i === 0 || i === blurredImg.width - 1) && (j === 0 || j === blurredImg.height -1)) {
        assert(pixelEq(blurredImg.getPixel(i,j), expectedAvgCorner));
      }
      else { assert(pixelEq(blurredImg.getPixel(i,j), expectedAvgEdge)); }
    }
  }
});


//const img = lib220.loadImageFromURL("https://people.cs.umass.edu/~joydeepb/robot.jpg");
const img = lib220.loadImageFromURL("https://f4.bcbits.com/img/a1780799975_16.jpg");
const r = removeBlueAndGreen(img);
const g = makeGrayscale(img);
const h = highlightEdges(img);
const b = blur(img);
img.show(); r.show(); g.show(); h.show(); b.show();
*/