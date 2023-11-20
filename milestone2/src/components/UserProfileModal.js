import React from 'react';

const UserProfileModal = ({ user, onClose }) => {
  return (
    <div className="user-profile-modal">
      <h3>User Profile</h3>
      <p>Name: {user.name}</p>
      <p>Email: {user.email}</p>

      {user.orders && user.orders.length > 0 ? (
        <>
          <h4>Recent Orders:</h4>
          <ul>
            {user.orders.map((order, index) => (
              <li key={index}>
                Order ID: {order.orderId}, Total: {order.totalAmount}, Date: {order.orderDate}
              </li>
            ))}
          </ul>
        </>
      ) : (
        <p>No recent orders</p>
      )}

      <button onClick={onClose}>Close</button>
    </div>
  );
};

export default UserProfileModal;
