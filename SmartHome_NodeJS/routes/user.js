const express = require('express');
const router = express.Router();
let firebase = require("firebase");

const firebaseConfig = {
    apiKey: "AIzaSyDoOCoszWOJ3-JIUvAYKQPKcLj6P0PuI-M",
    authDomain: "smarthome-50b1d.firebaseapp.com",
    databaseURL: "https://smarthome-50b1d.firebaseio.com",
    projectId: "smarthome-50b1d",
    storageBucket: "smarthome-50b1d.appspot.com",
    messagingSenderId: "1051706511319",
    appId: "1:1051706511319:web:e89d93225957802fff8592",
    measurementId: "G-YJMPQRWZE5"
  };
  
    if (!firebase.apps.length) {
      firebase.initializeApp(firebaseConfig);
      }

//로그인창
router.get('/loginForm', function(req, res, next) {
    const session =req.session.user; 
   
    res.render('loginForm',{session});
});
//회원가입 창
router.get('/joinForm', function(req, res, next) {
    const session =req.session.user; 

    res.render('joinForm',{session});
});
//우리집 상태창
router.get('/myhome',function(req, res, next){
    firebase.database().ref('HomeState').once('value',function(snapshot){
        const childData = snapshot.val();
        
        const session =req.session.user
        
        res.render('myhome',{childData,session});
    })   
});

//로그아웃
router.get('/logOut', function(req, res, next) {
    req.session.destroy();
    res.redirect('../');
});

//집 상태 변경하기(버튼클릭시)
router.get('/state_save',function(req,res,next){
    for(const key in req.query){
        console.log(key, req.query[key]);
        firebase.database().ref('HomeState/'+key).set(req.query[key])

    }
    const session =req.session.user;
    res.redirect("/user/myhome");
});

//로그인 post
router.post('/loginChk', function(req, res, next) {
    firebase.auth().signInWithEmailAndPassword(req.body.id, req.body.passwd)
       .then(function(firebaseUser) {
 
            console.log(req.body.id);
            console.log(req.body.passwd);
            req.session.user = req.body.id;
            res.redirect('../');    
       })
      .catch(function(error) {
          //로그인 실패
          res.send('로그인정보가 일치하지 않습니다.');
      });   
});

//회원가입 post
router.post('/joinChk', function(req, res, next){
    firebase.auth().createUserWithEmailAndPassword(req.body.email, req.body.password)
        .then(function(firebaseUser){
            const session =req.session.user;
                res.redirect('../',{session});
        })
        .catch(function(error){
            //가입실패
            res.send('이미있는 아이디이거나 오류입니다.');
        })
});

module.exports = router;