// App.js
import { useState } from 'react';
import { useNavigate } from 'react-router-dom';
import './login.css';
import App from './App';

function Login() {
  const [username, setUsername] = useState('');
  const [password, setPassword] = useState('');
  let navigate = useNavigate();
  const handleSubmit = (event) => {
    event.preventDefault();
    fetch('http://localhost:8080/api/students/login', {
      method: 'POST',
      body: JSON.stringify({
        "username": username, "password": password
      }),
      headers: {
        'Content-type': 'application/json; charset=UTF-8',
      },
    })
      .then((response) => response.json())
      .then((data) => {
        console.log(data);
        if (data === true) {
          navigate('/App');
        }else{
          alert("Incorrect username or password");
        }
      })
      .catch((err) => {
        console.log(err.message);
      });
  };
  return (
    <div className='container'>
      <h2>Student Login</h2>
      <form onSubmit={handleSubmit}>
        <input
          type="text"
          value={username}
          onChange={(e) => setUsername(e.target.value)}
          placeholder="Username"
        />
        <input
          type="password"
          value={password}
          onChange={(e) => setPassword(e.target.value)}
          placeholder="Password"
        />
        <button type="submit">Login</button>
      </form>
    </div>
  );
}

export default Login;