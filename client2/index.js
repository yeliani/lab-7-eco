let socket = io("http://localhost:5050/", { path: "/real-time" });


function setEmotion(emotion) {
  socket.emit("emotion", emotion);
}

function setLight(color) {
  socket.emit("semaforo", color);
}
