import React from 'react';

const UserProfilePage = ({ user }) => {
  return (
    <div className="container mt-4">
      <h2>User Profile</h2>
      <div className="card">
        <div className="card-body">
          <h5 className="card-title">User Information</h5>
          <p><strong>Name:</strong> {user.name}</p>
          <p><strong>Email:</strong> {user.email}</p>
          {/* Add other user information as needed */}
        </div>
      </div>
    </div>
  );
};

export default UserProfilePage;
