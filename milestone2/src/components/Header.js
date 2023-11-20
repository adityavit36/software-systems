import React, { useState } from 'react';
import '../App.css';
import UserProfileModal from './UserProfileModal'; // Import UserProfileModal component

function Header(props) {
  const [searchQuery, setSearchQuery] = useState('');
  const [isUserProfileOpen, setIsUserProfileOpen] = useState(false);

  const handleSubmit = (e) => {
    e.preventDefault();
    props.handleSearch(searchQuery);
  };

  const openUserProfile = () => {
    setIsUserProfileOpen(true);
  };

  const closeUserProfile = () => {
    setIsUserProfileOpen(false);
  };

  return (
    <nav className="navbar navbar-expand-lg navbar-dark bg-primary">
      <a
        className="navbar-brand"
        href="#"
        onClick={() => props.handleShow(false)}
      >
        <i className="fas fa-shopping-cart"></i> ShopEasy Kart
      </a>

      <button
        className="navbar-toggler"
        type="button"
        data-toggle="collapse"
        data-target="#navbarNav"
        aria-controls="navbarNav"
        aria-expanded="false"
        aria-label="Toggle navigation"
      >
        <span className="navbar-toggler-icon"></span>
      </button>

      <div className="collapse navbar-collapse" id="navbarNav">
        <form
          className="form-inline mx-auto my-2 my-lg-0"
          onSubmit={handleSubmit}
        >
          <input
            className="form-control mr-sm-2"
            type="search"
            placeholder="Search For Products"
            aria-label="Search"
            value={searchQuery}
            onChange={(e) => setSearchQuery(e.target.value)}
          />
          <button className="btn btn-light my-2 my-sm-0" type="submit">
            <i className="fas fa-search"></i>
          </button>
        </form>

        <ul className="navbar-nav ml-auto">
          <li className="nav-item">
            <a
              className="nav-link"
              href="#"
              onClick={() => props.handleShow(true)}
            >
              <i className="fas fa-shopping-cart"></i> Cart
              <sup> {props.count} </sup>
            </a>
          </li>
          <li className="nav-item">
            <a className="nav-link" href="#" onClick={openUserProfile}>
              <i className="fas fa-user"></i> Profile
            </a>
          </li>
        </ul>
      </div>

      {isUserProfileOpen && (
  <UserProfileModal user={props.user || {}} onClose={closeUserProfile} />
      )}
    </nav>
  );
}

export default Header;
