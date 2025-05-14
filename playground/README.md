# Brakes cooling playground tool

```
 ______     ______     ______
/\  == \   /\  == \   /\__  _\
\ \  __<   \ \  __<   \/_/\ \/
 \ \_____\  \ \_\ \_\    \ \_\
  \/_____/   \/_/ /_/     \/_/

```

BEJUIT RACING TEAM

## Usage

### Method 1: Using http-server

1. Make sure you have [Node.js](https://nodejs.org/) installed on your machine.
2. Install `http-server` globally by running `npm install -g http-server`.
3. Clone or download this repository.
4. Navigate to the project directory in your terminal.
5. Run `http-server .` to start the server.
6. Open your web browser and go to `http://localhost:8080` to use the Fibonacci Calculator 3000.

### Method 2: Disabling CORS Protections

If you prefer not to use `http-server`, you can disable CORS protections in your web browser to run the application directly:

- For **Google Chrome**, you can use the `--disable-web-security` flag.
- For **Mozilla Firefox**, you can install the [CORS Everywhere](https://addons.mozilla.org/en-US/firefox/addon/cors-everywhere/) extension.

Please note that disabling CORS protections can have security implications. Use it only for local development purposes.

## Variables

TEMPERATURE_START_LOGGING
Valeur par défaut: 80.00
Température mesurée à partir de laquelle on commence à logger les données de température. Permet de ne pas enregistrer de log de température ayant peu de valeur : on ne commence à logger que quand les frains ont atteint cette température. Ne pas mettre une valeur trop importante, puisque cette valeur doit être atteinte par les deux freins en même temps.

## License

This project is licensed under the [MIT License](LICENSE). Feel free to use, modify, and distribute this code as you see fit.
