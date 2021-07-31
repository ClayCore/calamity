import * as controllers from './controllers/';

import compression from 'compression';
import express from 'express';
import path from 'path';

const app = express();

// TODO: support for running this on a hosted app.
app.set('port', process.env.PORT || 3000);
app.set('views', path.join(__dirname + '../views'));
app.set('view engine', 'pug');

app.use(compression);
app.use(express.json());
app.use(express.urlencoded({ extended: true }));

// TODO: clean this up
app.use(express.static(__dirname));
app.use(express.static(path.join(__dirname, 'public')));

app.get('/', controllers.index);

export default app;
