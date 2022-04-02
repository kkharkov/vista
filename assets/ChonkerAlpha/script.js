const section = document.querySelector("section");
const logo = document.querySelector(".logo");
const background = document.querySelector(".background");
//const debug = document.getElementById("debugText");
//const debug2 = document.getElementById("debugText2");
const audio = new Audio('audio.mp3');
const FPS = 165;


// Logo moving velocity Variables
let xPosition = (window.innerWidth/2);
let yPosition = (window.innerHeight/2);
//debug.innerHTML = (window.innerHeight/2);
//debug2.innerHTML = (window.innerWidth/2);

let xSpeed = 1;
let ySpeed = 1;
if (Math.round(Math.random()))
{
	xSpeed *= -1;
}
if (Math.round(Math.random()))
{
	ySpeed *= -1;
}

//Dogo thickness
let dogSize = 100;
let count = 0;

section.style.height = window.innerHeight + "px";
section.style.width = window.innerWidth + "px";
section.style.backgroundColor = 'rgba(255, 99, 71, 0.5)';
logo.style.height = dogSize + 'px';
logo.style.width = dogSize + 'px';

window.wallpaperPropertyListener = {
    applyUserProperties: function(properties) {
        if (properties.backgroundcolor) {
            var schemeColor = properties.backgroundcolor.value.split(' ');
            schemeColor = schemeColor.map(function(c) {
                return Math.ceil(c * 255);
            });
            var schemeColorAsCSS = 'rgb(' + schemeColor + ')';
			section.style.backgroundColor = schemeColorAsCSS;
        }
		if (properties.backgroundimage) {
			section.style.backgroundImage = "url('file:///" + properties.backgroundimage.value + "')";
			section.style.backgroundRepeat = "no-repeat";
			section.style.backgroundAttachment = "fixed";
			section.style.backgroundPosition = "center";
			if (properties.backgroundsize.value == 0)
			{
				section.style.backgroundSize = "cover";
			}else if (properties.backgroundsize.value == 1)
			{
				section.style.backgroundSize = "contain";
			}
        }
		if (properties.backgroundsize) {
			if (properties.backgroundsize.value == 0)
			{
				section.style.backgroundSize = "cover";
			}else if (properties.backgroundsize.value == 1)
			{
				section.style.backgroundSize = "contain";
			}
		}
		if (properties.dogothickness)
		{
			dogSize = properties.dogothickness.value;
			logo.style.height = dogSize + 'px';
			logo.style.width = dogSize + 'px';
		}
    },
};

function update() {
  logo.style.left = xPosition + "px";
  logo.style.top = yPosition + "px";
}

setInterval(() => {
  if (xPosition + logo.clientWidth >= window.innerWidth || xPosition <= 0) {
    xSpeed = -xSpeed;
  }
  if (yPosition + logo.clientHeight >= window.innerHeight || yPosition <= 0) { // window.innerHeight-29 before
    ySpeed = -ySpeed;
  }
  xPosition += xSpeed;
  yPosition += ySpeed;
  update();
}, 200 / FPS);

window.addEventListener("resize", () => {
  xPosition = 10;
  yPosition = 10;

  section.style.height = window.innerHeight + "px";
  section.style.width = window.innerWidth + "px";
});

function dogeClicked()
{
	audio.pause();
	audio.currentTime = 0;
	logo.style.height = (dogSize*0.9) + 'px';
	logo.style.width = (dogSize*0.9) + 'px';
	setTimeout(() => { 
	logo.style.height = dogSize + 'px';
	logo.style.width = dogSize + 'px';}, 100);
	audio.volume = 0.2;
	audio.play();	
}

