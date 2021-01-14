const express = require('express');
const router = express.Router();
let firebase = require("firebase");
const dateFormat = require('dateformat');


//파이어베이스 연동 (DB)
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
  //1회만 연결하기위해
  if (!firebase.apps.length) {
    firebase.initializeApp(firebaseConfig);
    }

//헤더의 게시판버튼을 누르면 이동
router.get('board1', function(req, res, next) {
    res.redirect('boardList');
});

//게시판버튼을 누르면 실행 - boardList <게시판 글 리스트 가져오기>
router.get('/boardList', function(req, res, next) {
    //파이어베이스에서 ref('태그(테이블).orderByKey().once() --> board테이블 하위요소의 값을 가져와서 snapshot에 json형식으로 담겨있음
    firebase.database().ref('board').orderByKey().once('value', function(snapshot) {
        const rows = [];
        const session =req.session.user; 
        snapshot.forEach(function(childSnapshot) {
            
            //childData = 테이블 정보가 들어있는 객체 (key : value) ex)) brddate : 155555555, brdmemo : '게시물내용' ....
            const childData = childSnapshot.val();
            console.log('childData :',childData);
            childData.brddate = dateFormat(childData.brddate, "yyyy-mm-dd"); 
            //rows 배열에 담음
            rows.push(childData);
            console.log('rows:',rows);
        });
        
        //DB값을 boardList 뷰로 전송,
        res.render('boardList', {rows: rows, session});
    });
});

//글 불러오기 (리스트에 있는 글 클릭)
router.get('/boardRead', function(req, res, next) {
    firebase.database().ref('board/'+req.query.brdno).once('value', function(snapshot) {
        const childData = snapshot.val();    
        childData.brdno = snapshot.key; 
        childData.brddate = dateFormat(childData.brddate, "yyyy-mm-dd");

        const session =req.session.user;
        res.render('boardRead', {row: childData , session});
    });
});

//글 작성하기
router.get('/boardForm', function(req,res,next){
    const session =req.session.user;
    if (!req.query.brdno) {
        res.render('boardForm', {row: "", session});
        return;
    }
 
    firebase.database().ref('board/'+req.query.brdno).once('value', function(snapshot) {
        const childData = snapshot.val();
         
        childData.brdno = snapshot.key;
        
        res.render('board1/boardForm', {row: childData, session});
    });
});

//글 저장하기
router.post('/boardSave', function(req,res,next){
    const postData = req.body;
    if (!postData.brdno) {
        postData.brdno = firebase.database().ref().child('posts').push().key;
        postData.brddate = Date.now();
    } else {
        postData.brddate = Number(postData.brddate); 
    }
    firebase.database().ref('board/' + req.body.brdno).set(req.body);
 
    res.redirect('boardList');
});

//글 삭제하기
router.get('/boardDelete', function(req,res,next){
    firebase.database().ref('board/' + req.query.brdno).remove();
    res.redirect('boardList');
});
 
module.exports = router;
