webcamlist
cam=webcam(2);
preview(cam);
for i = 1:10
pause (1.0);
i = i+1;
end
image = snapshot(cam);
imshow(image);