/*
 * Kevin Vicente
 * February 2020
 *
 * The program is structured as follows: first we define helper functions, then the
 * functions specified in the homework document, then tests and finally the main function.
 * All code is written solely by myself.
 */

// Helper functions
// Return the average of the components of pixel p
function pixelAvg(p) {
  if (p.length !== 3) { return undefined; }
  else { return (p[0] + p[1] + p[2]) / 3; }
}

// Return the vector sum of a and b
function pixelAdd(a, b) {
  if (a.length !==3 || b.length !== 3) { return null; }
  else { a[0] += b[0]; a[1] += b[1]; a[2] += b[2]; return a; }
}

// Return the scalar product of pixel p and scalar s 
function pixelMult(p, s) {
  if (p.length !== 3) { return undefined; }
  else { p[0] *= s; p[1] *= s; p[2] *= s; return p; }
}


// imageMapXY(img: Image, func: (img: Image, x: number, y:number) => Pixel): Image
function imageMapXY(img, func) {
  let newImg = img.copy();
  for (let i = 0; i < img.width; i += 1) {
    for (let j = 0; j < img.height; j += 1) {
      newImg.setPixel(i, j, func(img, i, j));
    }
  }
  return newImg;
}
// imageMapXY(img: Image, func: (img: Image, x: number, y:number) => boolean, mask: Pixel): Image
function imageMask(img, func, mask) {
  return imageMapXY(img, function(img, x, y) {
    if (func(img, x, y)) { return mask; }
    else { return img.getPixel(x,y); }
  });
}

// blurPixel(img: Image, x: number, y: number): Pixel
function blurPixel(img, x, y) {
  let avgPixel = [0,0,0];
  let numNeighbors = 0;

  for (let dx = -1; dx <= 1; dx += 1) {
    for (let dy = -1; dy <= 1; dy += 1) {
      const nx = x + dx, ny = y + dy;
      // If the indices of the neighboring pixel are valid, compute the vector sum of the total sum
      // so far, and increment the number of neighbors added so far.
      if (nx >= 0 && ny >= 0 && nx < img.width && ny < img.height) {
        const pixel = img.getPixel(nx, ny);
        avgPixel = pixelAdd(avgPixel, pixel);
        numNeighbors += 1;
      }
    }
  }
  return pixelMult(avgPixel, 1 / numNeighbors);
}

function blurImage(img) {
  return imageMapXY(img, blurPixel);
}

function isGrayish(pixel) {
  return pixel[0] >= 0.3 && pixel[0] <= 0.7 &&
         pixel[1] >= 0.3 && pixel[1] <= 0.7 &&
         pixel[2] >= 0.3 && pixel[2] <= 0.7;
}

function toGrayscale(img) {
  return imageMapXY(img, function(img, x, y) {
    if (isGrayish(img.getPixel(x,y))) {
      const avg = pixelAvg(img.getPixel(x,y));
      return [avg,avg,avg];
    } else { return img.getPixel(x,y); }
  });
}

function saturateHigh(img) {
  return imageMapXY(img, function(img, x, y) {
    let pixel = img.getPixel(x,y);
    if (pixel[0] > 0.7) { pixel[0] = 1; }
    if (pixel[1] > 0.7) { pixel[1] = 1; }
    if (pixel[2] > 0.7) { pixel[2] = 1; }
    return pixel;
  });
}

function blackenLow(img) {
  return imageMapXY(img, function(img, x, y) {
    let pixel = img.getPixel(x,y);
    if (pixel[0] < 0.3) { pixel[0] = 0; }
    if (pixel[1] < 0.3) { pixel[1] = 0; }
    if (pixel[2] < 0.3) { pixel[2] = 0; }
    return pixel;
  });
}

// reduceFunctions(fns: ((p: Pixel) => Pixel)[]): (p: Pixel) => Pixel
function reduceFunctions(fns) {
  function compose(composed, newf) { return (x) => newf(composed(x)); }
  return fns.reduce(compose, (x) => x);
}

function colorize(img) {
  function blacken(pixel) {
    if (pixel[0] < 0.3) { pixel[0] = 0; }
    if (pixel[1] < 0.3) { pixel[1] = 0; }
    if (pixel[2] < 0.3) { pixel[2] = 0; }
    return pixel;
  }

  function saturate(pixel) {
    if (pixel[0] > 0.7) { pixel[0] = 1; }
    if (pixel[1] > 0.7) { pixel[1] = 1; }
    if (pixel[2] > 0.7) { pixel[2] = 1; }
    return pixel;
  }

  function gray(pixel) {
    if (isGrayish(pixel)) {
      const avg = pixelAvg(pixel);
      return [avg,avg,avg];
    } else { return pixel; }
  }

  let composition = reduceFunctions([blacken, saturate, gray]);
  return imageMapXY(img, function(img, x, y) {
    return composition(img.getPixel(x,y));
  });
}




// Tests below
function pixelEq (p1, p2) {
  const epsilon = 0.002;
  for (let i = 0; i < 3; ++i) {
    if (Math.abs(p1[i] - p2[i]) > epsilon) {
      return false;
    }
  }
  return true;
}


test("imageMapXY returns new image with same dimensions", function() {
  const img = lib220.createImage(3, 3, [0,0,0]);
  const newImg = imageMapXY(img, (img, x, y) => img.getPixel(x,y));
  assert(img !== newImg);
  assert(img.width === newImg.width);
  assert(img.height === newImg.height);
});

test("imageMapXY applies function correctly", function() {
  const blackImg = lib220.createImage(10, 10, [0,0,0]);
  const sameImg = imageMapXY(blackImg, (i,x,y) => i.getPixel(x,y));
  const whiteImg = imageMapXY(blackImg, (i, x, y) => [1,1,1]);

  for (let i = 0; i < whiteImg.width; i += 1) {
    for (let j = 0; j < whiteImg.height; j += 1) {
      assert(pixelEq(whiteImg.getPixel(i,j), [1,1,1]));
      assert(pixelEq(blackImg.getPixel(i,j), sameImg.getPixel(i,j)));
    }
  }
});

test("imageMapXY is defined for small images", function() {
  const emptyImg = lib220.createImage(1, 1, [0,0,0]);
  const sameImg = imageMapXY(emptyImg, (i,x,y) => i.getPixel(x,y));
  assert(sameImg !== emptyImg);
  assert(sameImg.width === 1);
  assert(sameImg.height === 1);
  assert(pixelEq(sameImg.getPixel(0,0), [0,0,0]));
});


test("imageMask returns new image with same dimensions", function() {
  const blackImg = lib220.createImage(3, 3, [0,0,0]);
  const whiteImg = imageMask(blackImg, (i,x,y) => true, [1,1,1]);
  assert(blackImg !== whiteImg);
  assert(blackImg.width === whiteImg.width);
  assert(blackImg.height === whiteImg.height);
});

test("imageMask applies function correctly", function() {
  function inUpperHalf(img, x, y) { return y < img.height / 2; }

  const blackImg = lib220.createImage(3, 3, [0,0,0]);
  const whiteImg = imageMask(blackImg, (i,x,y) => true, [1,1,1]);
  const sameImg = imageMask(blackImg, (i,x,y) => false, [1,1,1]);
  // Upper half will be white, lower half will be black.
  const splitImg = imageMask(blackImg, inUpperHalf, [1,1,1]);

  for (let i = 0; i < whiteImg.width; i += 1) {
    for (let j = 0; j < whiteImg.height; j += 1) {
      assert(pixelEq(whiteImg.getPixel(i,j), [1,1,1]));
      assert(pixelEq(sameImg.getPixel(i,j), [0,0,0]));
      if (inUpperHalf(splitImg, i, j)) {
        assert(pixelEq(splitImg.getPixel(i,j), [1,1,1]));
      } else {
        assert(pixelEq(splitImg.getPixel(i,j), [0,0,0]));
      }
    }
  }
});


/*
 * For the next few tests, we focus less on edge cases (e.g. small images) since they all utilize
 * the imageMapXY function that we tested earlier in the testing suite for edge cases. Thus, we
 * focus our attention on correct pixel values. We ignore edge cases for: blurPixel/blurImage,
 * toGrayscale/isGrayish, saturateHigh, and blackenLow.
 */

// This effectively tests both blurPixel and blurImage since blurImage is just a mapping of
// blurPixel to all pixels in an image.
test("blurPixel on edge pixels", function() {
  const pixelImg = lib220.createImage(1, 1, [0.5, 0.5, 0.5]);
  assert(pixelEq(blurPixel(pixelImg, 0, 0), [0.5, 0.5, 0.5]));

  let smallImg = lib220.createImage(3, 3, [0,0,0]);
  // This will make an image that has horizontal strips of color.
  // Red on top, green in the middle, blue on the bottom.
  for (let i = 0; i < smallImg.width; i += 1) {
    for (let j = 0; j < smallImg.height; j += 1) {
      let pixel = [0,0,0];
      pixel[j] = 1;
      smallImg.setPixel(i, j, pixel);
    }
  }
  const blurredImg = blurImage(smallImg);

  for (let i = 0; i < blurredImg.width; i += 1) {
    for (let j = 0; j < blurredImg.height; j += 1) {
      const pixel = blurredImg.getPixel(i,j);
      if (j === 0) { assert(pixelEq(pixel, [0.5, 0.5, 0])); }
      else if (j === 1) { assert(pixelEq(pixel, [0.333, 0.333, 0.333])); }
      else { assert(pixelEq(pixel, [0, 0.5, 0.5])); }
    }
  }
});


test("toGrayscale correctness", function() {
  // Test for a gray image, a grayish image, and a colorful (in this case, white) image.
  const grayImg = lib220.createImage(3, 3, [0.5, 0.5, 0.5]);
  const lessGrayImg = lib220.createImage(3, 3, [0.35, 0.5, 0.65]);
  const notGrayImg = lib220.createImage(3, 3, [1,1,1]);

  const sameImg = toGrayscale(grayImg);
  const moreGrayImg = toGrayscale(lessGrayImg);
  const whiteImg = toGrayscale(notGrayImg);

  assert(sameImg.width === grayImg.width && sameImg.height === grayImg.height);
  assert(lessGrayImg.width === moreGrayImg.width && lessGrayImg.height === moreGrayImg.height);
  assert(notGrayImg.width === whiteImg.width && notGrayImg.height === whiteImg.height);

  for (let i = 0; i < sameImg.width; i += 1) {
    for (let j = 0; j < sameImg.height; j += 1) {
      assert(pixelEq(grayImg.getPixel(i,j), sameImg.getPixel(i,j)));
      assert(pixelEq(moreGrayImg.getPixel(i,j), [0.5, 0.5, 0.5]));
      assert(pixelEq(notGrayImg.getPixel(i,j), whiteImg.getPixel(i,j)));
    }
  }
});


test("saturateHigh correctness", function() {
  // Test for a fully saturated image, a partially saturated image and an unsaturated image.
  const saturatedImg = lib220.createImage(3, 3, [0.8, 0.8, 0.8]);
  const greenSaturatedImg = lib220.createImage(3, 3, [0, 0.8, 0]);
  const notSaturatedImg = lib220.createImage(3, 3, [0.4, 0.4, 0.4]);

  const whiteImg = saturateHigh(saturatedImg);
  const fullGreenImg = saturateHigh(greenSaturatedImg);
  const sameImg = saturateHigh(notSaturatedImg);

  assert(saturatedImg.width === whiteImg.width && saturatedImg.height === whiteImg.height);
  assert(greenSaturatedImg.width === fullGreenImg.width && greenSaturatedImg.height === fullGreenImg.height);
  assert(notSaturatedImg.width === sameImg.width && notSaturatedImg.height === sameImg.height);

  for (let i = 0; i < sameImg.width; i += 1) {
    for (let j = 0; j < sameImg.height; j += 1) {
      assert(pixelEq(whiteImg.getPixel(i,j), [1,1,1]));
      assert(pixelEq(fullGreenImg.getPixel(i,j), [0,1,0]));
      assert(pixelEq(notSaturatedImg.getPixel(i,j), sameImg.getPixel(i,j)));
    }
  }
});


test("blackenLow correctness", function() {
  // Test for a dark image, a slightly dark image and a bright image.
  const blackishImg = lib220.createImage(3, 3, [0.2, 0.2, 0.2]);
  const grayImg = lib220.createImage(3, 3, [0.5, 0.2, 0.5]);
  const whiteImg = lib220.createImage(3, 3, [1,1,1]);

  const blackImg = blackenLow(blackishImg);
  const purpleImg = blackenLow(grayImg);
  const sameImg = blackenLow(whiteImg);

  assert(blackishImg.width === blackImg.width && blackishImg.height === blackImg.height);
  assert(grayImg.width === purpleImg.width && grayImg.height === purpleImg.height);
  assert(whiteImg.width === sameImg.width && whiteImg.height === sameImg.height);

  for (let i = 0; i < sameImg.width; i += 1) {
    for (let j = 0; j < sameImg.height; j += 1) {
      assert(pixelEq(blackImg.getPixel(i,j), [0,0,0]));
      assert(pixelEq(purpleImg.getPixel(i,j), [0.5, 0, 0.5]));
      assert(pixelEq(sameImg.getPixel(i,j), whiteImg.getPixel(i,j)));
    }
  }
});


test("reduceFunctions for simple arithmetic", function() {
  let f = (x) => x + 1;
  let g = (x) => 2 * x;
  let h = (x) => x * x;
  // Should compose functions in the order they are provided in the array
  // In this case, comp(a) = f(g(h(a)))
  let comp = reduceFunctions([f,g,h]);
  assert(comp(0) === 4);
  assert(comp(-1) === 0);
  assert(comp(1) === 16);
});

test("reduceFunctions on pixel -> pixel functions", function() {
  let f = function(p) { p[0] = 0; return p; };
  let g = function(p) { p[1] = 0; return p; };
  let h = function(p) { p[2] = 0; return p; };
  let c = reduceFunctions([f,g,h]);
  assert(pixelEq(c([1,1,1]), [0,0,0]));
});

test("reduceFunctions applied to an image", function() {
  const img = lib220.createImage(10, 10, [1,1,1]);
  let f = function(p) { p[0] = 0; return p; };
  let g = function(p) { p[1] = 0; return p; };
  let h = function(p) { p[2] = 0; return p; };
  let c = reduceFunctions([f,g,h]);
  const newImg = imageMapXY(img, (i, x, y) => c(i.getPixel(x,y)));
  for (let i = 0; i < newImg.width; i += 1) {
    for (let j = 0; j < newImg.height; j += 1) {
      assert(pixelEq(newImg.getPixel(i,j), [0,0,0]));
    }
  }
});


test("colorize correctness", function() {
  // This image will have 3 rows, each of which will be targeted by one of the three
  // functions that are applied by colorize.
  let img = lib220.createImage(3, 3, [0.2, 0.2, 0.2]);
  for (let i = 0; i < img.width; i += 1) {
    img.setPixel(i, 1, [0.5, 0.5, 0.5]);
    img.setPixel(i, 2, [0.8, 0.8, 0.8]);
  }
  let colorizedImg = colorize(img);

  assert(img.width === colorizedImg.width && img.height === colorizedImg.height);
  for (let i = 0; i < colorizedImg.width; i += 1) {
    assert(pixelEq(colorizedImg.getPixel(i, 0), [0,0,0]));
    assert(pixelEq(colorizedImg.getPixel(i, 1), [0.5, 0.5, 0.5]));
    assert(pixelEq(colorizedImg.getPixel(i, 2), [1,1,1]));
  }
});



// Main
/*
const url = "https://f4.bcbits.com/img/a1780799975_16.jpg";
const url = "https://f4.bcbits.com/img/a0534092560_10.jpg";
const url = "https://f4.bcbits.com/img/a4012200554_10.jpg";
*/
const url = "https://f4.bcbits.com/img/a0466802174_10.jpg";

let img = lib220.loadImageFromURL(url);
img.show();

blurImage(img).show();
toGrayscale(img).show();
saturateHigh(img).show();
blackenLow(img).show();
colorize(img).show();