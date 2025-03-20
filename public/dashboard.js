const client = mqtt.connect('ws://185.122.200.9:8083/mqtt');


client.on('connect', function () {
    console.log('connected to MQTT');
    client.subscribe("esp32/led/status", function (err) {
        if (err) {
                console.log('Subscription error: ', err);
        } else {
                console.log('sucess ...');
        }
    });
});

client.on('message', function (topic, message) {
    if (topic === 'esp32/led/status') {
        const ledStatus = message.toString();
        console.log('LED status: ', ledStatus);
        document.getElementById('ledStatus').innerText = ledStatus;
    }

});


document.getElementById('turnOn').addEventListener("click", () => {
    console.log('Turning LED ON');
    client.publish("esp32/led", "ON");
});

document.getElementById('turnOff').addEventListener("click", () => {
    console.log('Turning LED OFF');
    client.publish("esp32/led", "OFF");
});
