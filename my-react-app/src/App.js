// App.js
import React from 'react';
import StudentForm from './StudentForm'; // Check this import statement
import './App.css';
import 'bootstrap/dist/css/bootstrap.min.css';

function App() {
  return (
    <div className="app-container">
      <header>
        <h1>Student Information System</h1>
      </header>
      <main>
        <StudentForm />
      </main>
      <footer>
        <p>&copy; 2023 IIITB University</p>
      </footer>
    </div>
  );
}

export default App;
