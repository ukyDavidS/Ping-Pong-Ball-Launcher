webcamlist
  %%cam=webcam(1);
preview(cam); %%opens preview
for i = 30 %%For loop for preview
pause (1.0);
i = i+1;
end

closePreview(cam); %%closes preview
image = snapshot(cam); %%Takes picture
imtool(image); %%Opens imtool which can be used to measure

r_channel=image(:,:,1); %%Creates Red Pane image
g_channel=image(:,:,2); %%Creates Green Pane image
b_channel=image(:,:,3); %%Creates Blue Pane Image

levelr = 0.22; %%Red levels red pane
levelg = 0.25; %%Green Levels for green pane
levelb = 0.50; %%Blue levels for blue pane

ThrBlue = imbinarize(b_channel,levelb); %%Creates image with blue levels
ThrGreen = imbinarize(g_channel,levelg); %%Creates image with green levels
ThrRed = imbinarize(r_channel, levelr); %%Creates image with red levels

ThrSum = (~ThrRed&~ThrGreen&~ThrBlue); %%Sums up the blue, green, and red images

subplot(2,2,1), imshow(ThrRed); %%Plots red image with filter level
title('Red Plane')
subplot(2,2,2), imshow(ThrGreen); %%Plots green image with filter level
title('Green Plane')
subplot(2,2,3), imshow(ThrBlue); %%Plots blue image with filter level
title('Blue Plane')
subplot(2,2,4), imshow(ThrSum); %%Plots the summation image
title('Sum');
[centers,radii] = imfindcircles(ThrSum,[10 30]); %%Finds circles with radius of 10-30 pixels
c = viscircles(centers,radii); %%Displays the circles













