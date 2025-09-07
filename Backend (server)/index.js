const express = require("express");
const app = express();
const cors = require("cors");
const {uid} = require("uid");

app.use(cors());
let parkingData = {}
let reserved = []


app.use(express.urlencoded({extended: true}))

app.get("/",(req,res)=> {
  res.sendFile(__dirname+"/index.html")
})
app.get("/main",(req,res)=> {
  res.sendFile(__dirname+"/main.html",uid())
})
app.get("/getParking", (req, res) => {
  res.send(parkingData);
  const uid = req.query.uid;
});
app.get("/updateReserved",(req,res)=> {
  const uid = req.query.uid
  const slot = req.query.slot;
  reserved.push({uid, slot})
})
app.get("/getUid", (req, res) => {
  res.send(uid());
})

app.get("/updateParking", (req, res) => {
  console.log("request recieved .......");
  
  console.log(req.query);
  console.log(req.url);
  parkingData = req.query;
  console.log(parkingData);
})

app.listen(3001, () => {
  console.log("Server started on port 3001");
});
