let socket = io("http://localhost:5050/", { path: "/real-time" });

document.getElementById("turn-on-button").addEventListener("click", turnOnLed);
document.getElementById("turn-off-button").addEventListener("click", turnOffLed);
const body = document.querySelector("body")


function setEmotion(emotion) {
  socket.emit("emotion", emotion);
}

  
