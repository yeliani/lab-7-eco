let socket = io("http://localhost:5050/", { path: "/real-time" });


function setEmotion(emotion) {
  socket.emit("emotion", emotion);
}

function setLight(color) {
  socket.emit("semaforo", color);
}

const slider = document.getElementById("slider");
const valor = document.getElementById("valueLabel");

slider.addEventListener("input", () => {
  valor.textContent = slider.value;
  socket.emit("led3-intensity", parseInt(slider.value));
});