// index.js
import React from 'react';
import ReactDOM from 'react-dom';
import App from './App';
import './index.css'; // Add any global styling here
import {BrowserRouter as Router, Route, Routes} from 'react-router-dom';
import Login from './login.js';

ReactDOM.render(
  <React.StrictMode>
      <Router>
    <Routes>
     <Route exact path="/" element={<Login/>}></Route>
     <Route  path="/App" element={<App/>}></Route>
    </Routes>
    </Router>
  </React.StrictMode>,
  document.getElementById('root')
);
