import React from 'react';

const UserProfilePage = ({ user }) => {
  return (
    <div>
      <h2>User Profile Page</h2>
      <p>Name: {user.name}</p>
      <p>Email: {user.email}</p>
      {/* Add more user profile information */}
    </div>
  );
};

export default UserProfilePage;