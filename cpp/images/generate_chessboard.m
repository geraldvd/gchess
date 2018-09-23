clear all, close all, clc;

% Settings
l = 50;
w = [255,255,255];
b = 0.75*[163,102,41];

% Define squares
sw = uint8(ones(l, l, 3));
sb = uint8(ones(l, l, 3));

% Define colors
for i = 1:3
   sw(:,:,i) = w(i);
   sb(:,:,i) = b(i);
end

% Generate board
I = [sw sb sw sb sw sb sw sb;
     sb sw sb sw sb sw sb sw;
     sw sb sw sb sw sb sw sb;
     sb sw sb sw sb sw sb sw;
     sw sb sw sb sw sb sw sb;
     sb sw sb sw sb sw sb sw;
     sw sb sw sb sw sb sw sb;
     sb sw sb sw sb sw sb sw;];


% Result
imshow(I);
imwrite(I, 'chessboard.png');
