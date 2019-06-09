const http=require('http');
const express = require('express');
const mysql = require('mysql');
const TokenGenerator = require('uuid-token-generator');
const cors=require('cors');

const tokgen = new TokenGenerator(128, TokenGenerator.BASE62);

let app=express();
app.use(express.json());
app.use(cors());

//ToDo- WEB

app.post("/login",(req,res,callbackSS)=>{
    console.log("Request on /login");
    callbackSS=function(status){
        res.status(status).send();
    };

    let con=mysql.createConnection({
        host: "localhost",
        user: "southpaw",
        password: "password",
        database: "door",
        port: "3306"
    });

    let utag=req.body.utag;
    let upassword=req.body.upassword;
    let login=req.body.login;
    console.log(utag);
    console.log(upassword);
    console.log(login);

    con.connect((err)=>{
        if (err) console.log(err);
        let sql="select userid from users where utag like '"+utag+"';";
        con.query(sql,(err,res)=>{
            if(err) console.log(err);
            if(res.length==0){
                console.log("user with this utag doesnt exists");
                let utag=req.body.utag;
                let upassword=req.body.upassword;
                let login=req.body.login;
                let insertSQL="INSERT INTO users(login,utag,upassword) VALUES('"+login+"','"+utag+"','"+upassword+"');";
                con.query(insertSQL,(err)=>{
                    if(err) console.log(err);
                    console.log("I have inserted data to database!");
                });
                callbackSS(200);
            }
            con.end();
        });
    });
});

app.listen(1203,()=>{
    console.log("Sever listening on port 1203");
});