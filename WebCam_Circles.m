  %%webcamlist
  %%cam=webcam(1);
preview(cam); %%opens preview
for i = 10 %%For loop for preview
pause (1.0);
i = i+1;
end

closePreview(cam); %%closes preview
image = snapshot(cam); %%Takes picture
%%imtool(image); %%Opens imtool which can be used to measure

r_channel=image(:,:,1); %%Creates Red Pane image
g_channel=image(:,:,2); %%Creates Green Pane image
b_channel=image(:,:,3); %%Creates Blue Pane Image

br_ratio=double(b_channel)./double(r_channel);
bg_ratio=double(b_channel)./double(g_channel);

b_bin=(br_ratio>=1.5 & bg_ratio >= 1.5);
bw_circles=bwareaopen(b_bin,50);
imshow(bw_circles)

[centers,radii] = imfindcircles(bw_circles,[5 23]); %%Finds circles with radius of 10-20 pixels
c = viscircles(centers,radii); %%Displays the circles

distance = (0.7889.*(radii.*radii)-(33.576.*radii)+441.02)













