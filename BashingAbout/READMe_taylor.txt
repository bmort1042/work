You will need to import imagemagick on your computer for this to work.

sudo apt-get install imagemagick

Next make sure you have set the +x bit on the script so it will run

I put all my bash scripts in /usr/local/bin, then add that to my PATH by export PATH=$PATH:/usr/local/bin.
You should be able to run the scripts in this folder from anywhere now.

The script is written to save where ever the file is executed, so make sure you run it where you want to save the images.
