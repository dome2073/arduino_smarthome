const express = require('express');
const router = express.Router();

/* GET home page. */
router.get('/', function(req, res, next) {
 
   const session =req.session.user
   res.render('index', {session});
});

router.get('/test',function(req, res, next) {
  res.render('test');
});

module.exports = router;
